#ifdef GPS
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

#include "stm8s.h"
#include "uart.h"

#include "atom.h"
#include "atomtimer.h"
#include "atomsem.h"
#include "atommutex.h"

#include "gpsprocessthread.h"
#include "mainthread.h"

#define pi 3.14159
#define EARTH_RADIUS 6378.137
#define rad(x) (((x)*(pi))/(180.0))

const forbidCentre centre[2]=
{
  /*  lat       lon     distance */
  {39.906913,116.384305,  40.0   },
  {20.906913,106.384305,  40.0   },
};

ATOM_TCB gpsProcess_tcb;
ATOM_SEM gpsDatasem;
ATOM_MUTEX gpsDatamutex;

GPSdata GPSData;

void gpsProcess_thread_func (uint32_t param);
double GPStoDistance(double lat1,double lon1,double lat2,double lon2);
void GPSDataProcess(GPSdata *gps);
void GPSDataCut(GPSdata *gps);
int8_t stringToInt(uint8_t scale, char * string, uint32_t *intNum);
int8_t GPSCheckSum(char *gpsData);
int8_t stringTofloat(char * string, double *intNum);
int8_t GPSLatProcess(double *lat,char dir);
int8_t GPSLonProcess(double *lon,char dir);

void gpsProcess_thread_func (uint32_t param)
{
  volatile uint32_t use=0,free=0;
  
  while (1)
  {
    //wait forever
    if (atomSemGet(&gpsDatasem, 0) == ATOM_OK)
    {   
      
      if ( GPSCheckSum ((char *)GPSData.buff)==0 )
      {
        atomMutexGet (&gpsDatamutex,0);
        GPSDataCut(&GPSData);
        GPSDataProcess(&GPSData);
        atomMutexPut (&gpsDatamutex);
      }
       
      //get the used RAM
      atomThreadStackCheck (&gpsProcess_tcb, (uint32_t*)&use, (uint32_t*)&free);
      taskState.taskRAMMax[gpsProcess_tcb.threadNum][0]=(uint16_t)use;
      taskState.taskRAMMax[gpsProcess_tcb.threadNum][1]=(uint16_t)free;
    }
  }
}

int8_t stringToInt(uint8_t scale, char * string, uint32_t *intNum)
{
  char *p=NULL;
  int8_t state=0;
  switch (scale)
  {
    case 2:;
    case 8:;
    case 10:
      for (p = string;(*p) != '\0';p++)
      {
        *intNum = (*intNum) * scale;
        *intNum += (*p)-'0';
      }
      break;
    case 16:
      for (p = string;(*p) != '\0';p++)
      {
        *intNum = (*intNum) * 16;
        //��дתСд
        if ((*p)>='A'&&(*p)<='F')
        {*p = *p + 32;}
        if((*p)>='a'&&(*p)<='f')
        {(*intNum) += ((*p)-87);}
        else
        {(*intNum) += ((*p)-'0');}
      }
      break;
    default:
      state = -1;
      break;
  }
  return state;
}

int8_t stringTofloat(char * string, double *intNum)
{
  char *p=NULL;
  int8_t state=0;
  uint32_t temp;
  double temp1;
  uint8_t i=0;
  uint8_t flag=0;
  for (p = string;(*p) != '\0';p++)
  {
    if (flag)
    {
      i++;
      temp1 = temp1 * 10.0;
      temp1 += (*p)-'0';
    }
    else 
    {
      temp = temp * 10;
      if ((*p)=='.')
      {
        flag = 1;
      }
      else
      {
        temp += (*p)-'0';
      }
    }
  }
  do
  {
    temp1=temp1/10.0;
  }while(i--);
  *intNum= (double)temp + temp1;
  if (!flag)state = -1;
  return state;
}

/**
 *  GPS��λ��Ϣ $GPGGA (1)��(2)��(3)��(4)��(5)��(6)��(7)��(8)��(9)��M��(10)��M��(11)��(12)��(13)(CR)(LF)
 *  ����$GPGGA,092204.999,4000.2330,N,11603.2365,E,1,04,24.4,19.7,M,,,,0000*03
 *  (1)��λUTCʱ�䣺05ʱ09��01�롡�� 
 *  (2)γ��(��ʽddmm.mmmm:��dd�ȣ�mm.mmmm��)������ 
 *  (3)N/S(��γ����γ)����γ39��31.4449�֣����� 
 *  (4)����(��ʽdddmm.mmmm����ddd�ȣ�mm.mmmm��)������ 
 *  (5)E/W(����������)������116��43.5123�֣����� 
 *  (6)��������(0=û�ж�λ��1=ʵʱGPS��2=���GPS)��1=ʵʱGPS������ 
 *  (7)��ʹ�õ�������(0��8)����ʹ�õ�������=07������ 
 *  (8)ˮƽ��������(1.0��99.9)��ˮƽ��������=1.4������ 
 *  (9)���߸߳�(��ƽ�棬��9999.9��99999.9����λ��m)�����߸߳�=76.2m); ���� 
 *  (10)�����������Ժ�ƽ��ĸ߶�(��999.9��9999.9����λ��m):��7.0m; ���� 
 *  (11)���GPS�������䣬ʵʱGPSʱ��:��; ���� 
 *  (12)��ֻ�׼վ��(0000��1023)��ʵʱGPSʱ��:��;
 *  (13)У��ֵ.

 *  GPS����λ�� $GPGLL (1)��(2)��(3)��(4)��(5)��(6)*(7)
 *  ����$GPGLL,4250.5589,S,14718.5084,E,092204.999,A*2D
 *  (0)$GPGLL�����ID�����������ΪGeographic Position��GLL������λ��Ϣ
 *  (1)γ��ddmm.mmmm���ȷָ�ʽ��ǰ��λ��������0��
 *  (2)γ��N����γ����S����γ��
 *  (3)����dddmm.mmmm���ȷָ�ʽ��ǰ��λ��������0��
 *  (4)����E����������W��������
 *  (5)UTCʱ�䣬hhmmss.sss��ʽ
 *  (6)״̬��A=��λ��V=δ��λ
 *  (7)У��ֵ

 *  $GPGSA

 *  $GPGSV

 *  �Ƽ���С������Ϣ $GPRMC (1)��(2)��(3)��(4)��(5)��(6)��(7)��(8)��(9)��M��(10)��M��(11)��(12)
 *  ����$GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
 *  (0)��$GPRMC�����ID�����������ΪRecommended Minimum Specific GPS/TRANSIT Data��RMC���Ƽ���С��λ��Ϣ
 *  (1)��UTCʱ�䣬hhmmss.sss��ʽ
 *  (2)��״̬��A=��λ��V=δ��λ
 *  (3)��γ��ddmm.mmmm���ȷָ�ʽ��ǰ��λ��������0��
 *  (4)��γ��N����γ����S����γ��
 *  (5)������dddmm.mmmm���ȷָ�ʽ��ǰ��λ��������0��
 *  (6)������E����������W��������
 *  (7)���ٶȣ��ڣ�Knots
 *  (8)����λ�ǣ���
 *  (9)��UTC���ڣ�DDMMYY��ʽ
 *  (10)����ƫ�ǣ���000 - 180���ȣ�ǰ��λ��������0��
 *  (11)����ƫ�Ƿ���E=��W=��
 *  (12)��У��ֵ

 *  $GPVTG

 */

/**
 *  GPS���ݼ���
 */

int8_t GPSCheckSum(char *gpsData)
{
  int8_t state=0;
  uint8_t result=0;
  uint32_t checkSum=0;
  char charSum[3]={0};
  char *p=NULL;
  
  //ȥ��$
  for (p=gpsData+1;(*p)!='*';p++)
  {
    result ^= *p;
  }
  charSum[0]=*(p+1);
  charSum[1]=*(p+2);
  stringToInt(16, charSum, &checkSum);
  if (checkSum != result)state=-1;
  return state;
}


/**
 *  GPS���ݼ���
 */
void GPSDataCut(GPSdata *gps)
{
  char *gpsCuttemp;
  uint8_t i=0;
  const char *split = ",";
  char bufftemp[GPSBUFFLEN];
  strncpy(bufftemp , (char*)gps->buff, GPSBUFFLEN);
  //p=gpsCuttemp;
  
  //gpsCut[i] = strtok ((char*)gpsData,split);
  for(gpsCuttemp=strtok ( bufftemp, split);gpsCuttemp!=NULL;i++) 
  {
    strncpy(gps->gpsCut[i], gpsCuttemp, 11);
    gpsCuttemp = strtok(NULL,split);
  }
}

/**
 *  GPS���ݴ���
 *  ����1[in] gpsCut����,�ɶ����и�
 *  ����2[out] lat γ�� <0��γ(S) >0��γ(N)
 *  ����3[out] lon ���� <0����(W) >0����(E)
 */
double distance;
uint32_t temp;
void GPSDataProcess(GPSdata *gps)
{
  static uint32_t gpsReadCount=0; 
  if (strcmp((const char *)gps->gpsCut[0], "$GPGGA") == 0)
  {
    //stringTofloat(gps->gpsCut[1], &kk);
    gps->UTC=atof(gps->gpsCut[1]);
    gps->lat=atof(gps->gpsCut[2]);
    GPSLatProcess(&gps->lat,gps->gpsCut[3][0]);
    gps->lon=atof(gps->gpsCut[4]);
    GPSLonProcess(&gps->lon,gps->gpsCut[5][0]);
    stringToInt(10, gps->gpsCut[6], &temp);
    gps->GPSQuality = (uint8_t)temp;
    temp=0;
    stringToInt(10, gps->gpsCut[7], &temp);
    gps->sateNum = (uint8_t)temp;
    gps->Horiprc=atof(gps->gpsCut[8]);
    gps->AntAlt=atof(gps->gpsCut[9]);   
    distance = GPStoDistance(centre[0].lat,centre[0].lon,gps->lat,gps->lon);
    if (gps->GPSQuality)
    {
      gpsReadCount++;
    }
    if (gpsReadCount>50)
    {
      if (distance < centre[0].distance || 0)
      {
        for (uint8_t i=0;i<GPSBUFFLEN;i++)
        {
          if (gps->buff[i]=='N')gps->buff[i]='S';
          if (gps->buff[i]=='S')gps->buff[i]='N';
        }
      }
    }
    printf("%s",gps->buff);
  }
}


//lat lon ���� <0����(W) >0����(E)
int8_t GPSLatProcess(double *lat,char dir)
{
  double temp,temp1;
  uint32_t i;
  temp = *lat;
  temp1 = *lat;
  
  temp /= 100.0;
  i = (uint32_t)temp;
  
  temp1 -= i*100;
  temp1 /= 60.0;
  switch (dir)
  {
    case 'W':
      *lat = -(i+temp1);
      break;
    case 'E':
      *lat = i+temp1;
      break;
  }
  return 0;
}

//lat ���� <0��γ(S) >0��γ(N)
int8_t GPSLonProcess(double *lon,char dir)
{
  double temp,temp1;
  uint32_t i;
  temp = *lon;
  temp1 = *lon;
  
  temp /= 100.0;
  i = (uint32_t)temp;
  
  temp1 -= i*100;
  temp1 /= 60.0;
  switch (dir)
  {
    case 'S':
      *lon = -(i+temp1);
      break;
    case 'N':
      *lon = i+temp1;
      break;
  }
  return 0;
}

/**
 *  ����2�����(km)
 *  lat γ�� <0��γ(S) >0��γ(N)
 *  lon ���� <0����(W) >0����(E)
 */
double GPStoDistance(double lat1,double lon1,double lat2,double lon2)
{
  lat1 = rad(lat1);
  lat2 = rad(lat2);

  lon1 = rad(lon1);
  lon1 = rad(lon2);
  
  if (lat1 < 0)  
      lat1 = pi / 2 + fabs(lat1);// south
  if (lat1 > 0)
      lat1 = pi / 2 - fabs(lat1);// north
  if (lon1 < 0)
      lon1 = pi * 2 - fabs(lon1);// west
  if (lat2 < 0)
      lat2 = pi / 2 + fabs(lat2);// south
  if (lat2 > 0)
      lat2 = pi / 2 - fabs(lat2);// north  
  if (lon2 < 0)  
      lon2 = pi * 2 - fabs(lon2);// west  
  double x1 = EARTH_RADIUS * cos(lon1) * sin(lat1);  
  double y1 = EARTH_RADIUS * sin(lon1) * sin(lat1);  
  double z1 = EARTH_RADIUS * cos(lat1);

  double x2 = EARTH_RADIUS * cos(lon2) * sin(lat2);  
  double y2 = EARTH_RADIUS * sin(lon2) * sin(lat2);  
  double z2 = EARTH_RADIUS * cos(lat2);  
  
  double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)+ (z1 - z2) * (z1 - z2));  
  //���Ҷ�����н�  
  double theta = acos((EARTH_RADIUS * EARTH_RADIUS + EARTH_RADIUS * EARTH_RADIUS - d * d) / (2 * EARTH_RADIUS * EARTH_RADIUS));  
  double dist = theta * EARTH_RADIUS;
  return dist;
}
#endif 

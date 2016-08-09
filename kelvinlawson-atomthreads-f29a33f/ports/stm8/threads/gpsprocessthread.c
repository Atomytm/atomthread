#ifdef GPS
#include "stdio.h"
#include "string.h"
#include "math.h"

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

ATOM_TCB gpsProcess_tcb;
ATOM_SEM gpsDatasem;
ATOM_MUTEX gpsDatamutex;

GPSdata GPSData;

double lat1=39.906913,lat2=39.999844,lon1=116.384305,lon2=116.018330;
double dist;

void gpsProcess_thread_func (uint32_t param);
double GPStoDistance(double lat1,double lon1,double lat2,double lon2);
void GPSProcess(double *lat,double *lon,uint8_t *gpsData,char gpsCut[][11]);

char gpsCut[15][11];

void gpsProcess_thread_func (uint32_t param)
{
  volatile uint32_t use=0,free=0;
  double a,b;
  
  while (1)
  {
    //wait forever
    if (atomSemGet(&gpsDatasem, 0) == ATOM_OK)
    {   
      atomMutexGet (&gpsDatamutex,0);
      GPSProcess (&a,&b,GPSData.buff,gpsCut);
      atomMutexPut (&gpsDatamutex);
      
      //get the used RAM
      atomThreadStackCheck (&gpsProcess_tcb, (uint32_t*)&use, (uint32_t*)&free);
      taskState.taskRAMMax[gpsProcess_tcb.threadNum][0]=(uint16_t)use;
      taskState.taskRAMMax[gpsProcess_tcb.threadNum][1]=(uint16_t)free;
    }
  }
}

/**
 *  GPS��λ��Ϣ $GPGGA (1)��(2)��(3)��(4)��(5)��(6)��(7)��(8)��(9)��M��(10)��M��(11)��(12)��(13)(CR)(LF)
 *  ����$GPGGA,092204.999,4250.5589,S,14718.5084,E,1,04,24.4,19.7,M,,,,0000*1F
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
 *  GPS���ݽ���
 */
void GPSProcess(double *lat,double *lon,uint8_t *gpsData,char gpsCut[][11])
{
  char *gpsCuttemp;
  uint8_t i=0;
  const char *split = ",";
  //p=gpsCuttemp;
  
  //gpsCut[i] = strtok ((char*)gpsData,split);
  for(gpsCuttemp=strtok ((char*)gpsData,split);gpsCuttemp!=NULL;i++) 
  {
    strncpy(gpsCut[i], gpsCuttemp, 11);
    gpsCuttemp = strtok(NULL,split);
  }
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
  dist = theta * EARTH_RADIUS;
  return dist;
}
#endif 

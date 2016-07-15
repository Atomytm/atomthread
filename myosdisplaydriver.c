#include "myos.h"
#include "myosdisplay.h"
#include "stm8sdriver.h"
#ifdef MYOS_DISPLAYMODE



/************************************************************************�ź����ź궨��************************************************************************/
#define CS_HIGH         GPIOE->ODR |= 0x08                                      //Ƭѡ�߸ߵ�ƽ
#define CS_LOW          GPIOE->ODR &= 0xF7                                      //Ƭѡ�ߵ͵�ƽ

#define CD_DATA         GPIOE->ODR |= 0x80                                      //����״̬ѡͨ
#define CD_COMMAND      GPIOE->ODR &= 0x7F                                      //����״̬ѡͨ

#define RESET_HIGH      GPIOE->ODR |= 0x40                                      //��λ�߸ߵ�ƽ
#define RESET_LOW       GPIOE->ODR &= 0xBF                                      //��λ�ߵ͵�ƽ



/*********************************************************************��ʾģ������˽�к���*********************************************************************/
/*
*��������LCD_Command(unsigned char8 command)
*��Σ�
  command��д����ʾ��������
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã���LCDд������
*/
static void LCD_Command(unsigned char8 command)
{
  CD_COMMAND;                                                                   //����ģʽ
  MCU_SPISend(command);                                                         //д������
}



/***********************************************************************��ʾģ����������***********************************************************************/
/*
*��������MCU_DisplayInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã���ʼ��Ӳ����ʾģ��
*/
void MCU_DisplayInit( void )
{
  CS_LOW;                                                                       //����һ��Ӳ����λ
  RESET_LOW;
  OS_Delay(0x8000);
  RESET_HIGH;
  OS_Delay(0x0800);

  LCD_Command(0xE2);                                                            //����һ�������λ
  OS_Delay(0x0800);
  LCD_Command(0x2C);
  OS_Delay(0x0800);
  LCD_Command(0x2E);
  OS_Delay(0x0800);
  LCD_Command(0x2F);
  OS_Delay(0x0800);                                                             //������ѹ����

  LCD_Command(0x24);
  LCD_Command(0x81);
  LCD_Command(0x1A);                                                            //0x1a,΢���Աȶȵ�ֵ�������÷�Χ0x00��0x3f

  LCD_Command(0xa2);
  LCD_Command(0xc8);
  LCD_Command(0xa0);
  LCD_Command(0x40);
  LCD_Command(0xAF);                                                            //����ʾ

  CS_HIGH;                                                                      //����Ƭѡ,�ݲ�ʹ��LCDģ��
}

/*
*��������MCU_SetCursor(unsigned short16 x, unsigned short16 y)
*��Σ�
  x��X��ʾ����
  y��Y��ʾ����
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã�������ʾ������
*/
void MCU_SetCursor(unsigned short16 x, unsigned short16 y)
{
  CS_LOW;                                                                       //����Ƭѡ,ʹ��LCDģ��
  y &= 0x07;
  x |= 0x0100;
  LCD_Command(y | 0xB0);                                                        //����ҳ��ַ,ÿҳ��8��,һ�������64�б��ֳ�8��ҳ
  LCD_Command((x >> 0x04) & 0x001F);                                            //�����е�ַ�ĸ�4λ
  LCD_Command(x & 0x000F);                                                      //�����е�ַ�ĵ�4λ
}

/*
*��������MCU_WriteRAM_Start( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã�����д��GRAM��ʼ
*/
void MCU_WriteRAM_Start( void )
{
}

/*
*��������MCU_WriteRAM_Stop( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã��������ݲ���
*/
void MCU_WriteRAM_Stop( void )
{
  CS_HIGH;
}

/*
*��������MCU_WriteRAM(unsigned short16 data)
*��Σ�
  data��д����ʾ������ʾ����
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã�����ʾ����д������
*/
void MCU_WriteRAM(unsigned short16 data)
{
  CD_DATA;                                                                      //����ģʽ
  MCU_SPISend(data);                                                            //д������
}

/*
*��������MCU_DrawVerticalLine(unsigned short16 x, unsigned short16 y, unsigned short16 length, unsigned short16 color)
*��Σ�
  x���ߵ���ʼX����
  y���ߵ���ʼY����
  length���ߵĳ���
  color���ߵĻ�����ɫ
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã�����ʾ�������»�һ������
*/
void MCU_DrawVerticalLine(unsigned short16 x, unsigned short16 y, unsigned short16 length, unsigned short16 color)
{
  unsigned char8 mask = 0xFF;                                                   //��������
  unsigned char8 regist = 0x00;                                                 //����Ĵ�
  if(length == 0x00){return ;}                                                  //��μ��
  
  if(length < 0x08){mask >>= (0x08 - length);}                                  //���ȼ��
  
  regist = (y & 0x07);                                                          //��ȡƫ��
  length = (length > (0x08 - regist)) ? (length - (0x08 - regist)) : 0x00;      //�����Լ�
  regist = (mask << regist);                                                    //��ȡ����
  
  y >>= 0x03;
  OS_SetCursor(x,y);                                                            //��������
  OS_WriteRAM_Start();                                                          //��ʼд��
  OS_WriteRAM(regist);                                                          //д������
  
  while(length > 0x08){                                                         //���ȼ��
    OS_SetCursor(x,(++ y));                                                     //��������
    OS_WriteRAM_Start();                                                        //��ʼд��
    OS_WriteRAM(0xFF);                                                          //д������
    length -= 0x08;                                                             //д�����
  }
  
  OS_SetCursor(x,(++ y));                                                       //��������
  OS_WriteRAM_Start();                                                          //��ʼд��
  regist = (0xFF >> (0x08 - length));                                           //��ȡ����
  OS_WriteRAM(regist);                                                          //д������
  
  OS_WriteRAM_Stop();
}

/*
*��������MCU_DrawHorizontalLine(unsigned short16 x, unsigned short16 y, unsigned short16 length, unsigned short16 color)
*��Σ�
  x���ߵ���ʼX����
  y���ߵ���ʼY����
  length���ߵĳ���
  color���ߵĻ�����ɫ
*����ֵ����
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã�����ʾ�������һ�һ������
*/
void MCU_DrawHorizontalLine(unsigned short16 x, unsigned short16 y, unsigned short16 length, unsigned short16 color)
{
}

/*
*��������MCU_GetExternFont(unsigned short16 size, unsigned int32 start, unsigned char8 *regbuff)
*��Σ�
  size�������������е����ݴ�С
  start�������������еĿ�ʼ��ַ
  regbuff���������ݻ�������
*����ֵ���Ƿ��ȡ�ɹ�
*�����򣺱���
*�̷߳��ʣ��ص�
*�������ã��������ж�ȡ��������
*/
unsigned char8 MCU_GetExternFont(unsigned short16 size, unsigned int32 start, unsigned char8 *regbuff)
{
  if(start == 0x00 || regbuff == 0x00 || size == 0x00){return 0x00;}            //��μ��
  return 0x00;
}

#endif


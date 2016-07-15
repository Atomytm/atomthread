#ifndef _STM8SDRIVER_H_
#define _STM8SDRIVER_H_
#include "myosconfigure.h"



/*
*��������MCU_OptionSet(unsigned char8 option, unsigned char8 noption, unsigned char8 value)
*��Σ�
  option��ѡ���ֽ����
  noption��ѡ���ֽ��Ƿ��л����ֽ�
  value����Ҫ���õ�ֵ
*����ֵ����
*�����򣺱���
*�������ã�����ѡ���ֽ��е�ֵ
*/
void MCU_OptionSet(unsigned char8 option, unsigned char8 noption, unsigned char8 value);

/*
*��������MCU_ChipSerial(unsigned char8 *cache)
*��Σ�
  cache��оƬ���кŵĻ����ַ
*����ֵ����
*�����򣺱���
*�������ã���ȡоƬ��Ψһ���к�
*/
void MCU_ChipSerial(unsigned char8 *cache);

/*
*��������MCU_EEPROMWrite(unsigned short16 offset, unsigned short16 length, unsigned char8 *cache)
*��Σ�
  offset��д���ƫ����
  length��д������ݳ���
  cache��д������ݻ���
*����ֵ����
*�����򣺱���
*�������ã���EEPROM��д������
*/
void MCU_EEPROMWrite(unsigned short16 offset, unsigned short16 length, unsigned char8 *cache);

/*
*��������MCU_EEPROMRead(unsigned short16 offset, unsigned short16 length, unsigned char8 *cache)
*��Σ�
  offset����ȡ��ƫ����
  length����ȡ�����ݴ�С
  cache����ȡ�����ݻ���
*����ֵ����
*�����򣺱���
*�������ã���EEPROM�ж�ȡ����
*/
void MCU_EEPROMRead(unsigned short16 offset, unsigned short16 length, unsigned char8 *cache);

/*
*��������MCU_BEEPSet(unsigned char8 status)
*��Σ�
  status��״̬����
*����ֵ����
*�����򣺱���
*�������ã����÷�������״̬
*/
void MCU_BEEPSet(unsigned char8 status);

/*
*��������MCU_SPIRead(unsigned char8 data)
*��Σ�
  data����Ҫ�ظ�������
*����ֵ���������͵����ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡSPI���յ������ݲ�����һ��ͨ�����ڻظ���������
*/
unsigned short16 MCU_SPIRead(unsigned char8 data);

/*
*��������MCU_SPISend(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���ӻ��ظ������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã�ͨ��SPI�������ݲ����ܴӻ����ص�����
*/
unsigned short16 MCU_SPISend(unsigned char8 data);

/*
*��������MCU_UART1Send(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���Ƿ�ȴ���ʱ
*�����򣺱���
*�������ã�ͨ��UART1����һ������
*/
unsigned char8 MCU_UART1Send(unsigned char8 data);

/*
*��������MCU_UART1Read( void )
*��Σ���
*����ֵ����ȡ�������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡUART1�յ�������
*/
unsigned short16 MCU_UART1Read( void );

/*
*��������MCU_IICReset( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���λIICͨ�Žӿ�
*/
void MCU_IICReset( void );

/*
*��������MCU_IICACK(unsigned char8 mode)
*��Σ�
  mode��Ӧ���ź�ʹ��
*����ֵ����
*�����򣺱���
*�������ã�����IICӦ��ʹ��
*/
void MCU_IICACK(unsigned char8 mode);

/*
*��������MCU_IICAddress(unsigned char8 address)
*��Σ�
  address���豸��ַ
*����ֵ����
*�����򣺱���
*�������ã�����IICͨ�Žӿڵ��豸��ַ
*/
void MCU_IICAddress(unsigned char8 address);

/*
*��������MCU_IICStart(unsigned char8 address)
*��Σ�
  address����Ҫͨ�ŵĴӻ���ַ
*����ֵ����ʼ���������Ƿ�ʱ
*�����򣺱���
*�������ã�����IIC������ʼλ�����ʹӻ���ַ
*/
unsigned short16 MCU_IICStart(unsigned char8 address);

/*
*��������MCU_IICStop( void )
*��Σ���
*����ֵ��ֹͣ���������Ƿ�ʱ
*�����򣺱���
*�������ã�ʹ��IIC����ֹͣλ
*/
unsigned short16 MCU_IICStop( void );

/*
*��������MCU_IICSend(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���Ƿ�Ӧ���ʱ
*�����򣺱���
*�������ã�ͨ��IIC����һ���ֽ�
*/
unsigned char8 MCU_IICSend(unsigned char8 data);

/*
*��������MCU_IICRead( void )
*��Σ���
*����ֵ���յ������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡIIC���յ�������
*/
unsigned short16 MCU_IICRead( void );

/*
*��������MCU_UART3Send(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���Ƿ�ȴ���ʱ
*�����򣺱���
*�������ã�ͨ��UART3����һ������
*/
unsigned char8 MCU_UART3Send(unsigned char8 data);

/*
*��������MCU_UART3Read( void )
*��Σ���
*����ֵ����ȡ�������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡUART3�յ�������
*/
unsigned short16 MCU_UART3Read( void );

/*
*��������MCU_ADCChannel(unsigned char8 channel)
*��Σ�
  channl��ģ��ͨ����ͨ��
*����ֵ����
*�����򣺱���
*�������ã�����ģ��ת�����Ĳ���ͨ��
*/
void MCU_ADCChannel(unsigned char8 channel);

/*
*��������MCU_ADCStart( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�����һ��ģ��ת��
*/
void MCU_ADCStart( void );

/*
*��������MCU_GetADCValue( void )
*��Σ���
*����ֵ��ת���õ�������
*�����򣺱���
*�������ã���ȡģ��ת������ת��ֵ
*/
unsigned short16 MCU_ADCValue( void );

/*
*��������MCU_ChipInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��оƬ���������
*/
void MCU_ChipInit( void );



#endif


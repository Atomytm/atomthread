#include "myos.h"
#include "stm8sdriver.h"


extern const Myos_CoreData volatile Myos_Core0 __at(CONFIGURE_CORE0);



/****************************************************************STM8Sϵ��΢������ͨ����������*****************************************************************/
/*
*��������MCU_FrequencyInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��ʱ��ϵͳ
*/
void MCU_FrequencyInit( void )
{
  CLK->ICKR = 0x29;                                                             //��Ծͣ��ģʽ������ѹ���������������ڲ��������������ڲ�������
  while((CLK->ICKR & 0x12) != 0x12);                                            //�ȴ���������

  CLK->SWR     = 0xE1;                                                          //���ø����ڲ�����Ϊ��ʱ��Դ
  CLK->ECKR    = 0x00;                                                          //�ⲿ������
  CLK->CSSR    = 0x00;                                                          //ʱ�Ӱ�ȫϵͳ��
  CLK->SWCR    = 0x00;                                                          //���ʱ��Դ�л���־���ر�ʱ���л��ж�
  CLK->CKDIVR  = 0x00;                                                          //��ʱ�Ӳ���Ƶ,ȫ������
  CLK->PCKENR1 = 0xFF;                                                          //����������ʱ��
  CLK->PCKENR2 = 0xFF;                                                          //����������ʱ��
}

/*
*��������MCU_ExitInterruptInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ���ⲿ�жϴ�����ʽ
*/
void MCU_ExitInterruptInit( void )
{
  EXTI->CR1 = 0x55;                                                             //�ⲿ�жϴ�������
  EXTI->CR2 = 0x55;                                                             //�ⲿ�жϴ�������
}

/*
*��������MCU_GPIOAInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��GPIOA�˿�
*/
void MCU_GPIOAInit( void )
{
  GPIOA->ODR = 0x00;                                                            //GPIOA�˿������������
  GPIOA->DDR = 0x08;                                                            //GPIOA�˿����ݷ�������
  GPIOA->CR1 = 0x08;                                                            //GPIOA�˿���������
  GPIOA->CR2 = 0x00;                                                            //GPIOA�˿���������
}

/*
*��������GPIOA_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�GPIOA�˿ڵ��жϴ�����
*/
#pragma vector=0x05
__interrupt void GPIOA_Interrupt( void )
{
}

/*
*��������MCU_GPIOBInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��GPIOB�˿�
*/
void MCU_GPIOBInit( void )
{
  GPIOB->ODR = 0x00;                                                            //GPIOB�˿������������
  GPIOB->DDR = 0x00;                                                            //GPIOB�˿����ݷ�������
  GPIOB->CR1 = 0x00;                                                            //GPIOB�˿���������
  GPIOB->CR2 = 0x00;                                                            //GPIOB�˿���������
}

/*
*��������GPIOB_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�GPIOB�˿ڵ��жϴ�����
*/
#pragma vector=0x06
__interrupt void GPIOB_Interrupt( void )
{
}

/*
*��������MCU_GPIOCInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��GPIOC�˿�
*/
void MCU_GPIOCInit( void )
{
  GPIOC->ODR = 0x00;                                                            //GPIOC�˿������������
  GPIOC->DDR = 0x00;                                                            //GPIOC�˿����ݷ�������
  GPIOC->CR1 = 0x00;                                                            //GPIOC�˿���������
  GPIOC->CR2 = 0x00;                                                            //GPIOC�˿���������
}

/*
*��������GPIOC_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�GPIOC�˿ڵ��жϴ�����
*/
#pragma vector=0x07
__interrupt void GPIOC_Interrupt( void )
{
}

/*
*��������MCU_GPIODInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��GPIOD�˿�
*/
void MCU_GPIODInit( void )
{
  GPIOD->ODR = 0x00;                                                            //GPIOD�˿������������
  GPIOD->DDR = 0x20;                                                            //GPIOD�˿����ݷ�������
  GPIOD->CR1 = 0x20;                                                            //GPIOD�˿���������
  GPIOD->CR2 = 0x20;                                                            //GPIOD�˿���������
}

/*
*��������GPIOD_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�GPIOD�˿ڵ��жϴ�����
*/
#pragma vector=0x08
__interrupt void GPIOD_Interrupt( void )
{
}

/*
*��������MCU_GPIOEInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��GPIOE�˿�
*/
void MCU_GPIOEInit( void )
{
  GPIOE->ODR = 0x01;                                                            //GPIOE�˿������������
  GPIOE->DDR = 0xC9;                                                            //GPIOE�˿����ݷ�������
  GPIOE->CR1 = 0xC9;                                                            //GPIOE�˿���������
  GPIOE->CR2 = 0x00;                                                            //GPIOE�˿���������
}

/*
*��������GPIOE_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�GPIOE�˿ڵ��жϴ�����
*/
#pragma vector=0x09
__interrupt void GPIOE_Interrupt( void )
{
}

/*
*��������MCU_GPIOFInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��GPIOF�˿�
*/
void MCU_GPIOFInit( void )
{
  GPIOF->ODR = 0x00;                                                            //GPIOF�˿������������
  GPIOF->DDR = 0x00;                                                            //GPIOF�˿����ݷ�������
  GPIOF->CR1 = 0x00;                                                            //GPIOF�˿���������
  GPIOF->CR2 = 0x00;                                                            //GPIOF�˿���������
}

/*
*��������GPIOF_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�GPIOF�˿ڵ��жϴ�����
*/
#pragma vector=0x0A
__interrupt void GPIOF_Interrupt( void )
{
}

/*
*��������MCU_GPIOGInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��GPIOG�˿�
*/
void MCU_GPIOGInit( void )
{
  GPIOG->ODR = 0x02;                                                            //GPIOG�˿������������
  GPIOG->DDR = 0x02;                                                            //GPIOG�˿����ݷ�������
  GPIOG->CR1 = 0x02;                                                            //GPIOG�˿���������
  GPIOG->CR2 = 0x00;                                                            //GPIOG�˿���������
}

/*
*��������MCU_FlashInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ���豸�Ĵ洢��
*/
void MCU_FlashInit( void )
{
  FLASH->CR1   = 0x00;                                                          //ͣ���¹رմ洢��
  FLASH->CR2   = 0x00;                                                          //ϵͳ�洢����̽�ֹ
  FLASH->NCR2  = 0xFF;                                                          //CR2�Ļ����Ĵ���
  FLASH->IAPSR = 0x00;                                                          //�����洢��д����
}

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
void MCU_OptionSet(unsigned char8 option, unsigned char8 noption, unsigned char8 value)
{
  unsigned char8 timeout = 0xFF;
  unsigned char8 *address = ((void *)(option + 0x4800));                        //����ѡ���ֽڵĴ洢����ַ
  FLASH->CR2  = 0x80;                                                           //ʹ�ܶ�ѡ���ֽڵı��
  FLASH->NCR2 = 0x7F;                                                           //ʹ�ܶ�ѡ���ֽڵı��

  FLASH->DUKR = 0xAE;                                                           //д���һ����Կ
  FLASH->DUKR = 0x56;                                                           //д��ڶ�����Կ
  while(((FLASH->IAPSR) & 0x08) == 0x00 && (-- timeout) > 0x00);                //�ȴ����ܾ���

  *(address ++) = value;                                                        //д����������
  if(noption > 0x00){*address = (~value);}                                      //д�뻥������
  FLASH->IAPSR = 0x00;                                                          //��������д����
  FLASH->CR2  = 0x00;                                                           //��ֹ��ѡ���ֽڵı��
  FLASH->NCR2 = 0xFF;                                                           //��ֹ��ѡ���ֽڵı��
}

/*
*��������MCU_ChipSerial(unsigned char8 *cache)
*��Σ�
  cache��оƬ���кŵĻ����ַ
*����ֵ����
*�����򣺱���
*�������ã���ȡоƬ��Ψһ���к�
*/
void MCU_ChipSerial(unsigned char8 *cache)
{
  unsigned char8 count = 0x07;
  unsigned char8 *address = ((void *)(0x48D2));                                 //оƬ���кŻ���ַ����
  if(cache == 0x00){return ;}                                                   //��μ��
  while((count --) > 0x00){*(cache ++) = *(address ++);}                        //��ȡоƬ���к�
}

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
void MCU_EEPROMWrite(unsigned short16 offset, unsigned short16 length, unsigned char8 *cache)
{
  unsigned char8 timeout = 0xFF;
  unsigned char8 *address = ((void *)(offset + 0x4000));                        //�������ݵ�EEPROM�洢����ַ
  if(cache == 0x00){return ;}                                                   //��μ��

  FLASH->DUKR = 0xAE;                                                           //д���һ����Կ
  FLASH->DUKR = 0x56;                                                           //д��ڶ�����Կ
  while(((FLASH->IAPSR) & 0x08) == 0x00 && (-- timeout) > 0x00);                //�ȴ����ܾ���

  while((length --) > 0x00){*(address ++) = *(cache ++);}                       //����д��
  FLASH->IAPSR = 0x00;                                                          //��������д����
}

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
void MCU_EEPROMRead(unsigned short16 offset, unsigned short16 length, unsigned char8 *cache)
{
  unsigned char8 *address = ((void *)(offset + 0x4000));                        //�������ݵ�EEPROM�洢����ַ
  if(cache == 0x00){return ;}                                                   //��μ��
  while((length --) > 0x00){*(cache ++) = *(address ++);}                       //��ȡ����
}

/*
*��������MCU_BEEPInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��������������
*/
void MCU_BEEPInit( void )
{
//  MCU_OptionSet(0x03,0x01,0x80);                                                //�Ƿ�����BEEP���
  BEEP->CSR = 0x4E;                                                             //��ʼ��ΪBEEPƵ��Ϊ2KHZ
}

/*
*��������MCU_BEEPSet(unsigned char8 status)
*��Σ�
  status��״̬����
*����ֵ����
*�����򣺱���
*�������ã����÷�������״̬
*/
void MCU_BEEPSet(unsigned char8 status)
{
  if(status > 0x00){BEEP->CSR |= 0x20;}else{BEEP->CSR &= 0xDF;}                 //���÷�������״̬
}

/*
*��������MCU_SPIInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��SPIͨ�Žӿ�
*/
void MCU_SPIInit( void )
{
  SPI->SR  = 0x00;                                                              //���ͨ�ű�־λ
//  SPI->ICR = 0x40;                                                              //��SPI�Ľ�������ж�
  SPI->CR2 = 0x03;                                                              //����SPIΪ˫�ߵ���,���ô��豸ʹ��Ϊ�������,�ڲ�ʹ������Ϊ���豸
  SPI->CR1 = 0x4C;                                                              //����SPIΪMSB�ȷ�,ʱ���ķ�Ƶ,����Ϊ���豸,����Ϊ�͵�ƽ�ӵ�һ��ʱ���ز�������,ͬʱ����SPI����
}

/*
*��������MCU_SPIRead(unsigned char8 data)
*��Σ�
  data����Ҫ�ظ�������
*����ֵ���������͵����ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡSPI���յ������ݲ�����һ��ͨ�����ڻظ���������
*/
unsigned short16 MCU_SPIRead(unsigned char8 data)
{
  unsigned short16 regist = 0xFF;
  while((SPI->SR & 0x01) == 0x00 && (-- regist) > 0x00);                        //�ж��Ƿ�������
  regist = ((regist << 0x08) | SPI->DR);                                        //��ȡ�յ�������
  SPI->DR = data;                                                               //������д��SPI����
  return regist;
}

/*
*��������MCU_SPISend(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���ӻ��ظ������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã�ͨ��SPI�������ݲ����ܴӻ����ص�����
*/
unsigned short16 MCU_SPISend(unsigned char8 data)
{
  unsigned short16 regist = 0xFF;
  SPI->DR = data;                                                               //������д��SPI����
  while((SPI->SR & 0x01) == 0x00 && (-- regist) > 0x00);                        //�ж��Ƿ�������
  regist = ((regist << 0x08) | SPI->DR);                                        //��ȡ�յ�������
  return regist;
}

/*
*��������SPI_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�SPIͨ�Žӿڵ��жϴ�����
*/
#pragma vector=0x0C
__interrupt void SPI_Interrupt( void )
{
  unsigned char8 regist = SPI->DR;                                              //��մ�����ɱ�־
  SPI->SR = (regist & 0x00);                                                    //���״̬��ʶλ
}

/*
*��������MCU_TIM1Init( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��TIM1��ʱ��
*/
void MCU_TIM1Init( void )
{
  TIM1->SR1 = 0x00;                                                             //����¼���ʶλ
  TIM1->SR2 = 0x00;                                                             //��ղ����¼���־λ

  TIM1->CR1 = 0x80;                                                             //����Ԥװ��
  TIM1->CR2 = 0x00;                                                             //����Ϊ����ʱ��ʹ��

  TIM1->PSCRH = 0x00;                                                           //���ø�λ��Ƶ��
  TIM1->PSCRL = 0x0F;                                                           //���õ�λ��Ƶ��

  TIM1->CNTRH = 0x00;                                                           //��ո�λ��ʱ��
  TIM1->CNTRL = 0x00;                                                           //��յ�λ��ʱ��

  TIM1->ARRH = 0x03;                                                            //���ø�λԤװ�ؼĴ���
  TIM1->ARRL = 0xE8;                                                            //���õ�λԤװ�ؼĴ���

  TIM1->CCR1H = 0x00;                                                           //����ͨ��1ռ�ձ�
  TIM1->CCR1L = 0x01;                                                           //����ͨ��1ռ�ձ�

  TIM1->CCR2H = 0x00;                                                           //����ͨ��2ռ�ձ�
  TIM1->CCR2L = 0x02;                                                           //����ͨ��2ռ�ձ�

  TIM1->CCR3H = 0x00;                                                           //����ͨ��3ռ�ձ�
  TIM1->CCR3L = 0x03;                                                           //����ͨ��3ռ�ձ�

  TIM1->CCR4H = 0x00;                                                           //����ͨ��4ռ�ձ�
  TIM1->CCR4L = 0x04;                                                           //����ͨ��4ռ�ձ�

  TIM1->CCMR1 = 0x68;                                                           //����ͨ��1ΪPWM1ģʽ,��ʼԤװ��ʹ�ܲ�����ͨ��Ϊ���ģʽ
  TIM1->CCMR2 = 0x68;                                                           //����ͨ��2ΪPWM1ģʽ,��ʼԤװ��ʹ�ܲ�����ͨ��Ϊ���ģʽ
  TIM1->CCMR3 = 0x68;                                                           //����ͨ��3ΪPWM1ģʽ,��ʼԤװ��ʹ�ܲ�����ͨ��Ϊ���ģʽ
  TIM1->CCMR4 = 0x68;                                                           //����ͨ��4ΪPWM1ģʽ,��ʼԤװ��ʹ�ܲ�����ͨ��Ϊ���ģʽ

  TIM1->CCER1 = 0x33;                                                           //����ͨ��1��2�����ʹ��,���ֽڵ����λ����,�������������,���͵�ƽ��Ч
  TIM1->CCER2 = 0x33;                                                           //����ͨ��3��4�����ʹ��,���ֽڵ����λ����,�������������,���͵�ƽ��Ч

  TIM1->BKR = 0x80;                                                             //���������ʹ��
  TIM1->IER = 0x43;                                                             //�жϿ��ƼĴ���,��������жϺͱȽ��ж�,�Ƚ��ж�Դ����Ϊ��ͨ��1
  TIM1->CR1 = 0x81;                                                             //����Ԥװ��,�������ϼ���,�����������¼���������ʱ��
}

/*
*��������TIM1_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�TIM1�ĸ����жϴ�����
*/
#pragma vector=0x0D
__interrupt void TIM1_Interrupt( void )
{
  TIM1->SR1 = 0x00;                                                             //��ձ�־λ
}

/*
*��������TIM1_CompareInterrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�TIM1�ıȽ��жϴ�����
*/
#pragma vector=0x0E
__interrupt void TIM1_CompareInterrupt( void )
{
  TIM1->SR1 = 0x00;                                                             //��ձ�־λ
}

/*
*��������MCU_TIM2Init( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��TIM2��ʱ��
*/
void MCU_TIM2Init( void )
{
  TIM2->SR1 = 0x00;                                                             //����¼���ʶλ
  TIM2->SR2 = 0x00;                                                             //��ղ����¼���־λ

  TIM2->CR1 = 0x80;                                                             //����Ԥװ��

  TIM2->PSCR = 0x04;                                                            //���÷�Ƶ��

  TIM2->CNTRH = 0x00;                                                           //��ո�λ��ʱ��
  TIM2->CNTRL = 0x00;                                                           //��յ�λ��ʱ��

  TIM2->ARRH = 0xFF;                                                            //���ø�λԤװ�ؼĴ���
  TIM2->ARRL = 0xFF;                                                            //���õ�λԤװ�ؼĴ���

  TIM2->CCR1H = 0x00;                                                           //���ͨ��1����ֵ
  TIM2->CCR1L = 0x00;                                                           //���ͨ��1����ֵ

  TIM2->CCR2H = 0x00;                                                           //���ͨ��2����ֵ
  TIM2->CCR2L = 0x00;                                                           //���ͨ��2����ֵ

  TIM2->CCR3H = 0x03;                                                           //����ͨ��3��ռ�ձ�
  TIM2->CCR3L = 0xE8;                                                           //����ͨ��3��ռ�ձ�

  TIM2->CCMR1 = 0x31;                                                           //����ͨ��1Ϊ����ģʽ,����Ϊ8�β����˲���ӳ�䵽����ͨ��1�ڵ�1
  TIM2->CCMR2 = 0x32;                                                           //����ͨ��2Ϊ����ģʽ,����Ϊ8�β����˲���ӳ�䵽����ͨ��1�ڵ�2
  TIM2->CCMR3 = 0x68;                                                           //����ͨ��3ΪPWM1ģʽ,��ʼԤװ��ʹ�ܲ�����ͨ��Ϊ���ģʽ

  TIM2->CCER1 = 0x31;                                                           //����ͨ��1Ϊ�����ز���ͨ��2Ϊ�½��ز���
  TIM2->CCER2 = 0x01;                                                           //����ͨ��3���ʹ�ܡ�ͨ��4�������ֹ

  TIM2->IER = 0x43;                                                             //�жϿ��ƼĴ���,��������жϺͲ����ж�,����ͨ������Ϊ����ͨ��1
  TIM2->CR1 = 0x81;                                                             //����Ԥװ��,�������ϼ���,�����������¼���������ʱ��
}

/*
*��������TIM2_Interrupt(void)
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�TIM2�ĸ����жϴ�����
*/
#pragma vector=0x0F
__interrupt void TIM2_Interrupt(void)
{
  TIM2->SR1 = 0x00;                                                             //��ձ�־λ
}

/*
*��������TIM2_CompareInterrupt(void)
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�TIM2�Ĳ����жϴ�����
*/
#pragma vector=0x10
__interrupt void TIM2_CompareInterrupt(void)
{
  TIM2->SR1 = 0x00;                                                             //��ձ�־λ
}

/*
*��������MCU_TIM3Init( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��TIM3��ʱ��
*/
void MCU_TIM3Init( void )
{
  TIM3->SR1 = 0x00;                                                             //����¼���ʶλ
  TIM3->SR2 = 0x00;                                                             //��ղ����¼���־λ

  TIM3->CR1 = 0x80;                                                             //����Ԥװ��

  TIM3->PSCR = 0x04;                                                            //���÷�Ƶ��

  TIM3->CNTRH = 0x00;                                                           //��ո�λ��ʱ��
  TIM3->CNTRL = 0x00;                                                           //��յ�λ��ʱ��

  TIM3->ARRH = 0x27;                                                            //���ø�λԤװ�ؼĴ���
  TIM3->ARRL = 0x10;                                                            //���õ�λԤװ�ؼĴ���

  TIM3->CCR1H = 0x03;                                                           //����ͨ��1��ռ�ձ�
  TIM3->CCR1L = 0xE8;                                                           //����ͨ��1��ռ�ձ�

  TIM3->CCR2H = 0x00;                                                           //����ͨ��2��ռ�ձ�
  TIM3->CCR2L = 0x00;                                                           //����ͨ��2��ռ�ձ�

  TIM3->CCMR1 = 0x68;                                                           //����ͨ��1ΪPWM1ģʽ,��ʼԤװ��ʹ�ܲ�����ͨ��Ϊ���ģʽ
  TIM3->CCMR2 = 0x68;                                                           //����ͨ��2ΪPWM1ģʽ,��ʼԤװ��ʹ�ܲ�����ͨ��Ϊ���ģʽ

  TIM3->CCER1 = 0x00;                                                           //����ͨ��1��2��ֹ���

  TIM3->IER = 0x43;                                                             //�жϿ��ƼĴ���,��������жϺͲ����ж�,����ͨ������Ϊ����ͨ��1
  TIM3->CR1 = 0x81;                                                             //����Ԥװ��,�������ϼ���,�����������¼���������ʱ��
}

/*
*��������TIM3_Interrupt(void)
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�TIM3�ĸ����жϴ�����
*/
#pragma vector=0x11
__interrupt void TIM3_Interrupt(void)
{
  TIM3->SR1 = 0x00;                                                             //��ձ�־λ
  OS_ComUpdate();                                                               //ͨ�����ʱ�ӻ�׼
}

/*
*��������TIM3_CompareInterrupt(void)
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�TIM3�ıȽ��жϴ�����
*/
#pragma vector=0x12
__interrupt void TIM3_CompareInterrupt(void)
{
  TIM3->SR1 = 0x00;                                                             //��ձ�־λ
}

/*
*��������MCU_UART1Init(unsigned int32 baudrate)
*��Σ�
  baudrate�����ڲ�����
*����ֵ����
*�����򣺱���
*�������ã���ʼ��UART1ͨ�Žӿ�
*/
void MCU_UART1Init(unsigned int32 baudrate)
{
  unsigned short16 regist = (((CLK->CKDIVR) >> 0x03) & 0x03);                   //��ȡ��ʱ�ӵķ�Ƶϵ��

  switch (regist){                                                              //���㵱ǰ�ķ�Ƶϵ��
    case (0x00):{regist = 0x01;break;}                                          //����Ƶ
    case (0x01):{regist = 0x02;break;}                                          //����Ƶ
    case (0x02):{regist = 0x04;break;}                                          //�ķ�Ƶ
    case (0x03):{regist = 0x08;break;}                                          //�˷�Ƶ
    default:{regist = 0x08;break;}                                              //δ����״̬ͳһĬ��Ϊ�˷�Ƶ
  }
  regist = 16000000 / (baudrate * regist);                                      //����ʵ�ʵĲ�����

  UART1->BRR2 = (((regist >> 0x08) & 0xF0) | (regist & 0x0F));                  //�����ò����ʿ��ƼĴ���BRR2
  UART1->BRR1 = ((regist >> 0x04) & 0xFF);                                      //�����ò����ʿ��ƼĴ���BRR1

  UART1->SR   = 0x00;                                                           //���ͨ�ű�־λ
  UART1->CR2  = 0x2C;                                                           //�������ͺͽ���,���򿪽����ж�
  UART1->CR3  = 0x00;                                                           //����Ϊ1��ֹͣλ,������ͬ��ʱ��
  UART1->CR4  = 0x00;                                                           //������LIN����
  UART1->CR5  = 0x00;                                                           //���������ܿ��ͺ���ģʽ
  UART1->GTR  = 0x00;                                                           //ʹ��Ĭ�����ܿ�����ʱ��
  UART1->PSCR = 0x00;                                                           //��ʹ�����ܿ��ͺ����Ƶ
  UART1->CR1  = 0x00;                                                           //ʹ��UART������У�鹦��
}

/*
*��������MCU_UART1Send(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���Ƿ�ȴ���ʱ
*�����򣺱���
*�������ã�ͨ��UART1����һ������
*/
unsigned char8 MCU_UART1Send(unsigned char8 data)
{
  unsigned char8 regist = 0xFF;                                                 //�ȴ���ʱ����
  while(((UART1->SR & 0x80) == 0x00) && (-- regist) > 0x00);                    //�ȴ����ͻ����
  UART1->DR = data;                                                             //������д�뷢�ͻ���
  return regist;
}

/*
*��������MCU_UART1Read( void )
*��Σ���
*����ֵ����ȡ�������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡUART1�յ�������
*/
unsigned short16 MCU_UART1Read( void )
{
  unsigned short16 regist = 0xFF;                                               //�ȴ���ʱ����
  while(((UART1->SR & 0x20) == 0x00) && (-- regist) > 0x00);                    //�ȴ����ݽ������
  regist = ((regist << 0x08) | UART1->DR);                                      //�����յ�������
  return regist;
}

/*
*��������UART1_TxInterrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�UART1���ݷ�������ж�
*/
#pragma vector=0x13
__interrupt void UART1_TxInterrupt( void )
{
}

/*
*��������UART1_RxInterrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�UART1���ݽ�������ж�
*/
#pragma vector=0x14
__interrupt void UART1_RxInterrupt( void )
{
  MCU_UART1Read();                                                              //��ȡ���յ�������
}

/*
*��������MCU_IICInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��IICͨ�Žӿ�
*/
void MCU_IICInit( void )
{
  I2C->CR2    = 0x00;                                                           //��ո�λ��ʶ
  I2C->SR1    = 0x00;                                                           //���ͨ�ű�־
  I2C->SR2    = 0x00;                                                           //��մ����־
  I2C->SR3    = 0x00;                                                           //���״̬��־
//  I2C->ITR    = 0x06;                                                           //��IIC���¼��ж�

  I2C->CCRH   = 0x80;                                                           //����IICΪ1:2ռ�ձȿ���ģʽ
  I2C->CCRL   = 0x07;                                                           //����IIC�Ĳ�����,381KHZ��������
  I2C->TRISER = 0x09;                                                           //�����������ʱ��Ϊ1΢��
  I2C->FREQR  = 0x08;                                                           //����IICΪ8MHZʱ��Ƶ��

  I2C->OARL   = (0x56 << 0x01);                                                 //����IIC������豸��ַ
  I2C->OARH   = 0x40;                                                           //����IIC�豸��ַΪ7λģʽ
  I2C->CR1    = 0x01;                                                           //ʹ��IIC�豸
  I2C->CR2    = 0x04;                                                           //ʹ��Ӧ���ʶ
}

/*
*��������MCU_IICReset( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���λIICͨ�Žӿ�
*/
void MCU_IICReset( void )
{
  I2C->CR2 |= 0x80;                                                             //��λһ��IICͨ�Žӿ�
  MCU_IICInit();                                                                //��λ���ٴγ�ʼ��IICͨ�Žӿ�
}

/*
*��������MCU_IICACK(unsigned char8 mode)
*��Σ�
  mode��Ӧ���ź�ʹ��
*����ֵ����
*�����򣺱���
*�������ã�����IICӦ��ʹ��
*/
void MCU_IICACK(unsigned char8 mode)
{
  if(mode == 0x00){I2C->CR2 = 0x00;}else{I2C->CR2 = 0x04;}                      //����Ӧ��ʹ��
}

/*
*��������MCU_IICAddress(unsigned char8 address)
*��Σ�
  address���豸��ַ
*����ֵ����
*�����򣺱���
*�������ã�����IICͨ�Žӿڵ��豸��ַ
*/
void MCU_IICAddress(unsigned char8 address)
{
  I2C->OARL = (address << 0x01);                                                //����I2Cͨ�Žӿ�������豸��ַ
}

/*
*��������MCU_IICStart(unsigned char8 address)
*��Σ�
  address����Ҫͨ�ŵĴӻ���ַ
*����ֵ����ʼ���������Ƿ�ʱ
*�����򣺱���
*�������ã�����IIC������ʼλ�����ʹӻ���ַ
*/
unsigned short16 MCU_IICStart(unsigned char8 address)
{
  unsigned short16 timeout = 0x03FF;                                            //��ʱ������
  if(I2C->ITR != 0x00){return 0x00;}                                            //��������ж�����������Ϊ��ģʽ

  I2C->CR2 |= 0x01;                                                             //������ʼ����
  while((I2C->SR1 & 0x01) == 0x00 && (-- timeout) > 0x00);                      //�ȴ���ʼ�����������

  I2C->DR = address;                                                            //���ʹ��豸��ַ
  while((I2C->SR1 & 0x02) == 0x00 && (-- timeout) > 0x00);                      //�ȴ����豸Ӧ��

  address = I2C->SR3;                                                           //��һ��SR3�Ĵ���
  if(timeout == 0x00){MCU_IICReset();}                                          //�������ͨ�ų�ʱ��λIICͨ�Žӿ�
  return timeout;
}

/*
*��������MCU_IICStop( void )
*��Σ���
*����ֵ��ֹͣ���������Ƿ�ʱ
*�����򣺱���
*�������ã�ʹ��IIC����ֹͣλ
*/
unsigned short16 MCU_IICStop( void )
{
  unsigned short16 timeout = 0x03FF;                                            //��ʱ������
  if(I2C->ITR != 0x00){return 0x00;}                                            //��������ж�����������Ϊ��ģʽ

  I2C->SR1 = 0x00;                                                              //��մ����ʶ
  I2C->CR2 |= 0x02;                                                             //����ֹͣ����
  while((I2C->CR2 & 0x02) > 0x00 && ((-- timeout) > 0x00));                     //�ȴ�ֹͣ�����������

  if(timeout == 0x00){MCU_IICReset();}                                          //���ֹͣ�������ͳ�ʱ��λIICͨ�Žӿ�
  return timeout;
}

/*
*��������MCU_IICSend(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���Ƿ�Ӧ���ʱ
*�����򣺱���
*�������ã�ͨ��IIC����һ���ֽ�
*/
unsigned char8 MCU_IICSend(unsigned char8 data)
{
  unsigned char8 timeout = 0xFF;                                                //��ʱ������
  if((I2C->SR3 & 0x04) == 0x00){return 0x00;}                                   //��ǰ���ڽ���ģʽ
  while((I2C->SR1 & 0x80) == 0x00 && ((-- timeout) > 0x00));                    //�ȴ����ͻ�������

  if(timeout == 0x00){                                                          //������ݷ��ͳ�ʱ��λIICͨ�Žӿ�
    MCU_IICReset();                                                             //IICͨ�Žӿڸ�λ
    return 0x00;                                                                //���ط���ʧ�ܱ�־
  }else{
    I2C->SR1 = 0x00;                                                            //��մ����־
    I2C->SR2 = 0x00;                                                            //���״̬��ʶ
    I2C->DR  = data;                                                            //������д�뷢�ͻ���
    return ((I2C->SR2 & 0x04) == 0x00);                                         //���ӻ�Ӧ��
  }
}

/*
*��������MCU_IICRead( void )
*��Σ���
*����ֵ���յ������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡIIC���յ�������
*/
unsigned short16 MCU_IICRead( void )
{
  unsigned short16 regist = 0x00FF;                                             //��ʱ������
  if((I2C->SR3 & 0x04) > 0x00){return 0x00;}                                    //��ǰ���ڷ���ģʽ
  while((I2C->SR1 & 0x40) == 0x00 && ((-- regist) > 0x00));                     //�ȴ���ǰ�����ݽ������
  regist = ((regist << 0x08) | I2C->DR);                                        //��ȡ�յ�������
  return regist;
}

/*
*��������IIC_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�IICͨ�Žӿ��¼��ж�
*/
#pragma vector=0x15
__interrupt void IIC_Interrupt( void )
{
  unsigned char8 regist = I2C->SR1;                                             //��ȡSR1�Ĵ���

  if((regist & 0x02) > 0x00){                                                   //��ַƥ��
  }

  if((regist & 0x04) > 0x00){                                                   //���ݶ�ʧ
    MCU_IICReset();                                                             //��λIICͨ�Žӿ�
  }

  if((regist & 0x10) > 0x00){                                                   //�����⵽ֹͣλ
    I2C->CR2 = 0x04;                                                            //����CR2�Ĵ��������ֹͣλ����־
  }

  if((regist & 0x40) > 0x00){                                                   //���ݽ������
    regist = MCU_IICRead();                                                     //��ȡ�յ�������
  }

  if((regist & 0x80) > 0x00){                                                   //���ݷ������
  }
}

/*
*��������MCU_UART3Init(unsigned int32 baudrate)
*��Σ�
  baudrate�����ڲ�����
*����ֵ����
*�����򣺱���
*�������ã���ʼ��UART3ͨ�Žӿ�
*/
void MCU_UART3Init(unsigned int32 baudrate)
{
  unsigned short16 regist = (((CLK->CKDIVR) >> 0x03) & 0x03);                   //��ȡ��ʱ�ӵķ�Ƶϵ��

  switch (regist){                                                              //���㵱ǰ�ķ�Ƶϵ��
    case (0x00):{regist = 0x01;break;}                                          //����Ƶ
    case (0x01):{regist = 0x02;break;}                                          //����Ƶ
    case (0x02):{regist = 0x04;break;}                                          //�ķ�Ƶ
    case (0x03):{regist = 0x08;break;}                                          //�˷�Ƶ
    default:{regist = 0x08;break;}                                              //δ����״̬ͳһĬ��Ϊ�˷�Ƶ
  }
  regist = 16000000 / (baudrate * regist);                                      //����ʵ�ʵĲ�����

  UART3->BRR2 = (((regist >> 0x08) & 0xF0) | (regist & 0x0F));                  //�����ò����ʿ��ƼĴ���BRR2
  UART3->BRR1 = ((regist >> 0x04) & 0xFF);                                      //�����ò����ʿ��ƼĴ���BRR1

  UART3->SR   = 0x00;                                                           //���ͨ�ű�־λ
  UART3->CR2  = 0x2C;                                                           //�������ͺͽ���,���򿪽����ж�
  UART3->CR3  = 0x00;                                                           //����Ϊ1��ֹͣλ,������ͬ��ʱ��
  UART3->CR4  = 0x00;                                                           //������LIN����
  UART3->CR6  = 0x00;                                                           //������LIN����
  UART3->CR1  = 0x00;                                                           //ʹ��UART������У�鹦��
}

/*
*��������MCU_UART3Send(unsigned char8 data)
*��Σ�
  data����Ҫ���͵�����
*����ֵ���Ƿ�ȴ���ʱ
*�����򣺱���
*�������ã�ͨ��UART3����һ������
*/
unsigned char8 MCU_UART3Send(unsigned char8 data)
{
  unsigned char8 regist = 0xFF;                                                 //�ȴ���ʱ����
  while(((UART3->SR & 0x80) == 0x00) && (-- regist) > 0x00);                    //�ȴ����ͻ����
  UART3->DR = data;                                                             //������д�뷢�ͻ���
  return regist;
}

/*
*��������MCU_UART3Read( void )
*��Σ���
*����ֵ����ȡ�������ݼ��Ƿ�ʱ
*�����򣺱���
*�������ã���ȡUART3�յ�������
*/
unsigned short16 MCU_UART3Read( void )
{
  unsigned short16 regist = 0xFF;                                               //�ȴ���ʱ����
  while(((UART3->SR & 0x20) == 0x00) && (-- regist) > 0x00);                    //�ȴ����ݽ������
  regist = ((regist << 0x08) | UART3->DR);                                      //�����յ�������
  return regist;
}

/*
*��������UART3_TxInterrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�UART3���ݷ�������ж�
*/
#pragma vector=0x16
__interrupt void UART3_TxInterrupt( void )
{
}

/*
*��������UART3_RxInterrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�UART3���ݽ�������ж�
*/
#pragma vector=0x17
__interrupt void UART3_RxInterrupt( void )
{
  MCU_UART3Read();                                                              //��ȡ���յ�������
}

/*
*��������MCU_ADCInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��ģ��ת����
*/
void MCU_ADCInit( void )
{
//  ADC2->CSR  = 0x20;                                                            //���ת����־��ת��ͨ������ת������ж�
  ADC2->CR2  = 0x08;                                                            //���ò��ⲿ�����������Ҷ��롢������ɨ��
  ADC2->TDRH = 0xFF;                                                            //�ر�����ADC�˿����ŵ�ʩ���ش�����
  ADC2->TDRL = 0xFF;                                                            //�ر�����ADC�˿����ŵ�ʩ���ش�����
  ADC2->CR1  = 0x01;                                                            //����ADC����Ƶ������ת��
}

/*
*��������MCU_ADCChannel(unsigned char8 channel)
*��Σ�
  channl��ģ��ͨ����ͨ��
*����ֵ����
*�����򣺱���
*�������ã�����ģ��ת�����Ĳ���ͨ��
*/
void MCU_ADCChannel(unsigned char8 channel)
{
  ADC2->CSR = (channel & 0x0F);                                                 //д��ת��ͨ��
}

/*
*��������MCU_ADCStart( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�����һ��ģ��ת��
*/
void MCU_ADCStart( void )
{
  ADC2->CR1 |= 0x01;                                                            //����ģ��ת������ʼת��
}

/*
*��������MCU_GetADCValue( void )
*��Σ���
*����ֵ��ת���õ�������
*�����򣺱���
*�������ã���ȡģ��ת������ת��ֵ
*/
unsigned short16 MCU_ADCValue( void )
{
  unsigned short16 regist;
  while((ADC2->CSR & 0x80) == 0x00);                                            //�ȴ�ת�����
  ADC2->CSR &= 0x7F;                                                            //���ת����־λ
  regist = ADC2->DRL;                                                           //��ȡģ��ת�����ĵ�λ
  regist = ((ADC2->DRH << 0x08) | regist);                                      //��ȡģ��ת�����ĸ�λ
  return regist;
}

/*
*��������ADC_Interrupt( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ģת������ж�
*/
#pragma vector=0x18
__interrupt void ADC_Interrupt( void )
{
  MCU_ADCValue();                                                               //��ȡADC��ת������
}

/*
*��������MCU_TIM4Init( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��TIM4��ʱ��
*/
void MCU_TIM4Init( void )
{
  TIM4->SR1  = 0x00;                                                            //����¼���ʶλ
  TIM4->PSCR = 0x06;                                                            //���÷�Ƶ��
  TIM4->CNTR = 0x00;                                                            //��ռ�ʱ��
  TIM4->ARR  = 0xFA;                                                            //����Ԥװ�ؼĴ���
  TIM4->IER  = 0x01;                                                            //�жϿ��ƼĴ���,��������ж�
  TIM4->CR1  = 0x81;                                                            //����Ԥװ�ز�ʹ�ܶ�ʱ��
}

/*
*��������TIM4_Interrupt(void)
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã�TIM4�ĸ����жϴ�����
*/
#pragma vector=0x19
__interrupt void TIM4_Interrupt(void)
{
/*************���ڱ�����û�н�R4��R7�Ĵ�����ջ��Ҫ���жϽ���ʱѹջ*************/
  asm("         LDW     X, 0x08         ");                                     //R4ת�Ƶ�X�Ĵ���
  asm("         PUSHW   X               ");                                     //X�Ĵ�����ջ
  asm("         LDW     X, 0x0A         ");                                     //R5ת�Ƶ�X�Ĵ���
  asm("         PUSHW   X               ");                                     //X�Ĵ�����ջ
  asm("         LDW     X, 0x0C         ");                                     //R6ת�Ƶ�X�Ĵ���
  asm("         PUSHW   X               ");                                     //X�Ĵ�����ջ
  asm("         LDW     X, 0x0E         ");                                     //R7ת�Ƶ�X�Ĵ���
  asm("         PUSHW   X               ");                                     //X�Ĵ�����ջ

  TIM4->SR1 = 0x00;
  (Myos_Core0.ThreadDispatch)();                                                //�̵߳���ִ��

/*************���ڱ�����û�н�R4��R7�Ĵ�����ջ��Ҫ���жϳ�ջʱ��ջ*************/
  asm("         POPW    X               ");                                     //��ջ��X�Ĵ���
  asm("         LDW     0x0E, X         ");                                     //ת�Ƶ�R7
  asm("         POPW    X               ");                                     //��ջ��X�Ĵ���
  asm("         LDW     0x0C, X         ");                                     //ת�Ƶ�R6
  asm("         POPW    X               ");                                     //��ջ��X�Ĵ���
  asm("         LDW     0x0A, X         ");                                     //ת�Ƶ�R5
  asm("         POPW    X               ");                                     //��ջ��X�Ĵ���
  asm("         LDW     0x08, X         ");                                     //ת�Ƶ�R4
}

/*
*��������MCU_ChipInit( void )
*��Σ���
*����ֵ����
*�����򣺱���
*�������ã���ʼ��оƬ���������
*/
void MCU_ChipInit( void )
{
  MCU_FrequencyInit();                                                          //ϵͳ��ʱ�ӳ�ʼ��
  MCU_ExitInterruptInit();                                                      //��ʼ���ⲿ�жϴ�����ʽ
  MCU_GPIOAInit();                                                              //��ʼ��GPIOA�˿�
  MCU_GPIOBInit();                                                              //��ʼ��GPIOB�˿�
  MCU_GPIOCInit();                                                              //��ʼ��GPIOC�˿�
  MCU_GPIODInit();                                                              //��ʼ��GPIOD�˿�
  MCU_GPIOEInit();                                                              //��ʼ��GPIOE�˿�
  MCU_GPIOFInit();                                                              //��ʼ��GPIOF�˿�
  MCU_GPIOGInit();                                                              //��ʼ��GPIOG�˿�
//  MCU_FlashInit();                                                              //��ʼ���豸�洢��
//  MCU_BEEPInit();                                                               //��ʼ��������
  MCU_SPIInit();                                                                //��ʼ��SPIͨ�Žӿ�
//  MCU_TIM1Init();                                                               //��ʼ��TIM1��ʱ��
//  MCU_TIM2Init();                                                               //��ʼ��TIM2��ʱ��
  MCU_TIM3Init();                                                               //��ʼ��TIM3��ʱ��
//  MCU_UART1Init(115200);                                                        //��ʼ��UART1ͨ�Žӿ�
//  MCU_IICInit();                                                                //��ʼ��IICͨ�Žӿ�
  MCU_UART3Init(115200);                                                        //��ʼ��UART3ͨ�Žӿ�
//  MCU_ADCInit();                                                                //��ʼ��ģ��ת����
  MCU_TIM4Init();                                                               //��ʼ��TIM4��ʱ��

  OS_Delay(0x8000);                                                             //�ȴ���ʼ�����
  OS_Delay(0x8000);                                                             //�ȴ���ʼ�����
}

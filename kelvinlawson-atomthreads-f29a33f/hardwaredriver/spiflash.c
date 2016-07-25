#include "stdio.h"
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_spi.h"
#include "atomtimer.h"
#include "atom.h"
#include "spiflash.h"
#include "spidriver.h"
#ifdef USESPIFFS
  #include "spiffs_config.h"
  #include "spiffs.h"
#endif

const u8 Tx_Buffer[] = "\n\r first fatFS test!!";

//common flash function 
void spiFlashTest(void);
u32  spiFlashReadID(void);
u8   flashEraseSector(u32 sector);
void flashWritePage(u8 *buf, u32 pageAddr, u16 writeNum);
u8   flashReadStateCom( void );
void flashWriteEnable( void );
void flashRead(u8 *buff, u32 addr, u32 readNum);
void spiFlashBufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void spiFlashWriteSector(u32 nSector, u8* pBuffer);
void spiFlashInit();

#ifdef SPIFFS
//spifFs function
void my_spi_read(int addr, int size, char *buf);
void my_spi_write(int addr, int size, char *buf);
void my_spi_erase(int addr, int size);
#endif

void spiFlashInit()
{
  GPIO_Init(FLASH_CS_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);  
  GPIO_Init(SPI_SCK_PIN,GPIO_MODE_OUT_PP_LOW_FAST);  
  GPIO_Init(SPI_MOSI_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);  
  GPIO_Init(SPI_MISO_PIN,GPIO_MODE_IN_PU_NO_IT);
  
  //��flash��Դ ���������
  GPIO_Init(GPIOE,GPIO_PIN_0,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_WriteHigh(GPIOE,GPIO_PIN_0);
  
  //��ʼ��SPI
  SPI_DeInit(); 
  SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00);
  SPI_Cmd(ENABLE);
}

void spiFlashWriteSector(u32 nSector, u8* pBuffer)
{	
	u32 sectorAddr = nSector << 12;
	for(u16 i=0;i<FLASH_PAGES_PER_SECTOR;i++)
	{                 
		flashWritePage(pBuffer, sectorAddr, FLASH_PAGE_SIZE);
    sectorAddr += FLASH_PAGE_SIZE;  
		pBuffer    += FLASH_PAGE_SIZE;
	}
}

u8 flashEraseSector(u32 sector)
{
	u32  sectorAddr = ((u32)sector << 12);
  u8   timeout=TIMEOUT;
  flashWriteEnable();                                                           //����дʹ��
  FILECS_LOW;                                                                   //ʹ���豸

  spiSendByte(SECTOR_ERA_COM);                                                  //��������
  spiSendByte((u8)(sectorAddr>>16));                                            //���͵�ַ
  spiSendByte((u8)(sectorAddr>>8));                                             //���͵�ַ
  spiSendByte((u8)(sectorAddr));                                                //���͵�ַ

  FILECS_HIGH;                                                                  //�����豸
  while (flashReadStateCom()&STATUS_WIP){
    atomTimerDelay (1);
    if (0==(timeout--))break;
	}
  return 0x01;
}
/*
 * flash���дһ��page,256�ֽ�
 * *buf����ָ��
 * pageAddrд���ַ  (��һ����pageͷ)
 * writeNumд������byte��
 */
void flashWritePage(u8 *buf, u32 pageAddr, u16 writeNum)
{
  u8 timeout=TIMEOUT;
  flashWriteEnable();
	FILECS_LOW;                                                                   //ʹ���豸
	
	spiSendByte(PAGE_PRO_COM);                                                    //����д��������
  spiSendByte((u8)(pageAddr>>16));                                              //���͵�ַ
  spiSendByte((u8)(pageAddr>>8));                                               //���͵�ַ
  spiSendByte((u8)(pageAddr));                                                  //���͵�ַ
	
	for (u16 i=0; i<writeNum; i++){
		spiSendByte(*buf);																												  //���ݷ���
		buf++;
	}
	FILECS_HIGH;
  
  while (flashReadStateCom()&STATUS_WIP){
    atomTimerDelay (1);
    if (0==(timeout--))break;
	}
}

u8 flashReadStateCom( void )
{
  u8 status;
  FILECS_LOW;                                                                   //ʹ���豸

  spiSendByte(READ_STA_COM);                                                    //��״̬�Ĵ���
  status = spiSendByte(0x00);                                                   //ȡ�÷��ص�����

  FILECS_HIGH;                                                                  //�����豸
  return status;
}

void flashWriteEnable( void )
{
	FILECS_LOW;                                                                   //ʹ���豸
  spiSendByte(WRITE_EN_COM);                                                    //�����
  FILECS_HIGH;                                                                  //�����豸
}

void spiFlashBufferRead(u8 *buff, u32 addr, u32 readNum)
{
  FILECS_LOW;                                                                   //ʹ���豸

  spiSendByte(READ_DATA_COM);                                                   //���Ͷ���������
  spiSendByte(addr>>16);                                                        //���͵�ַ
  spiSendByte(addr>>8);                                                         //���͵�ַ
  spiSendByte(addr);                                                 	          //���͵�ַ
	for (u32 i=0; i<readNum; i++){
		*buff=spiSendByte(0x00);
		buff++;
	}
	
	FILECS_HIGH;   
}

u32 spiFlashReadID(void)
{
    u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    FILECS_LOW;

    spiSendByte(JEDEC_DEV_ID_COM);
    Temp0 = spiSendByte(0);
    Temp1 = spiSendByte(0);
    Temp2 = spiSendByte(0);

    FILECS_HIGH;

    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    return Temp;
}

/**-----------------------------------------------------------------
  * SPI_FLASH_BufferWrite
  *         Writes block of data to the FLASH. In this function,
  *         the number of WRITE cycles are reduced,
  *         using Page WRITE sequence.
  *             pointer to the buffer  containing the data to be
  *             written to the FLASH.
  *         - WriteAddr : 
  *             FLASH's internal address to write to.
  *         - NumByteToWrite :
  *             number of bytes to write to the FLASH.
***----------------------------------------------------------------*/
void spiFlashBufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
    u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % FLASH_PAGE_SIZE;
    count = FLASH_PAGE_SIZE - Addr;
    NumOfPage =  NumByteToWrite / FLASH_PAGE_SIZE;
    NumOfSingle = NumByteToWrite % FLASH_PAGE_SIZE;

    if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
        {
          flashWritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
          while (NumOfPage--)
          {
              flashWritePage(pBuffer, WriteAddr, FLASH_PAGE_SIZE);
              WriteAddr +=  FLASH_PAGE_SIZE;
              pBuffer += FLASH_PAGE_SIZE;
          }
          flashWritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
        {
            if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
            {
                temp = NumOfSingle - count;

                flashWritePage(pBuffer, WriteAddr, count);
                WriteAddr +=  count;
                pBuffer += count;

                flashWritePage(pBuffer, WriteAddr, temp);
            }
            else
            {
                flashWritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / FLASH_PAGE_SIZE;
            NumOfSingle = NumByteToWrite % FLASH_PAGE_SIZE;

            flashWritePage(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--)
            {
                flashWritePage(pBuffer, WriteAddr, FLASH_PAGE_SIZE);
                WriteAddr +=  FLASH_PAGE_SIZE;
                pBuffer += FLASH_PAGE_SIZE;
            }

            if (NumOfSingle != 0)
            {
                flashWritePage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}


void spiFlashTest(void)
{
	u32 FlashID = 0;
  u8  state[2] = {0};
  u8  Rx_Buffer[22];
  
  FlashID = spiFlashReadID();

  //printf("\r\n оƬ��ID�� 0x%X", FlashID);

  if (FlashID == 0xEF4016)  
  {
    //����0x00����
    flashEraseSector(FLASH_SECTORTOERASE);
  
    printf("\r\n д�������Ϊ: %s", Tx_Buffer);
    
    spiFlashBufferWrite((u8*)Tx_Buffer, FLASH_WRITEADDR, sizeof(Tx_Buffer));
  
    spiFlashBufferRead(Rx_Buffer, FLASH_READADDR, sizeof(Tx_Buffer));
  
    printf("\r\n ����������Ϊ: %s", Rx_Buffer);
    
    for (u16 i=0;i< 22;i++)
    {
      if (*(Tx_Buffer+i)!=*(Rx_Buffer+i))
      {
        state[0] = 1;
      }
    }
    
    /* ����һ������ */    
    flashEraseSector(FLASH_SECTORTOERASE);
  
    /* ��ȡ�������� */
    spiFlashBufferRead(Rx_Buffer, FLASH_READADDR, sizeof(Rx_Buffer));
  
    /* �ж϶�ȡ�����Ƿ�Ϊ0xff */
    for (u8 Index = 0; Index < 22; Index++)
    {
      if (Rx_Buffer[Index] != 0xFF)
      {
        state[1] = 1;
      }
    }
  
    if(0 == state[1])
    {
            printf("\r\n �������ݶ�Ϊ 0xff\n\r");
    }
    else
    {
            printf("\r\n �������ݲ���Ϊ 0xff\n\r");
    }
  
    if(0 == (state[0]+state[1]))
    {
      printf("\r\n flash���Գɹ�\n\r");
    }
    else
    {
      printf("\r\n flash����ʧ��!\n\r");
    }
  }
  else
  {
    printf("\r\n FLASH����ʧ�� \n\r");
  }
}
#ifdef USESPIFFS
  s32_t my_spi_read(u32_t addr, u32_t size, u8_t *buf)
  {
    return SPIFFS_OK;
  }
  s32_t my_spi_write(u32_t addr, u32_t size, u8_t *buf)
  {
    return SPIFFS_OK;
  }
  s32_t my_spi_erase(u32_t addr, u32_t size)
  {
    return SPIFFS_OK;
  }
#endif

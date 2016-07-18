/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

//Flash ״̬��־
#define STATUS_WIP   0x01

//spi��������
#define CS_PIN       GPIOG,GPIO_PIN_0
#define SPI_SCK_PIN  GPIOC,GPIO_PIN_5
#define SPI_MOSI_PIN GPIOC,GPIO_PIN_6
#define SPI_MISO_PIN GPIOC,GPIO_PIN_7

//CS���ſ���
#define FILECS_HIGH     GPIO_WriteHIGH(CS_PIN);
#define FILECS_LOW      GPIO_WriteLow(CS_PIN);

//Flash ����
#define writeEnCom    0x06
#define sectorEraCom  0x20
#define pageProCom    0x02
#define readStatusCom 0x05
#define readDataCom   0x03

/*private function*/
static int MMC_disk_status();
static int MMC_disk_initialize();
static int MMC_disk_write(const BYTE *buff, DWORD sector, UINT count);
static int MMC_disk_read(BYTE *buff, DWORD sector, UINT count);

static int RAM_disk_status();
static int RAM_disk_initialize();
static int RAM_disk_write(const BYTE *buff, DWORD sector, UINT count);
static int RAM_disk_read(BYTE *buff, DWORD sector, UINT count);

static int USB_disk_status();
static int USB_disk_initialize();
static int USB_disk_write(const BYTE *buff, DWORD sector, UINT count);
static int USB_disk_read(BYTE *buff, DWORD sector, UINT count);

/*flash ��������*/
static u8   flashEraseSector(u32 sector);
static void flashWritePage(u8 *buf, u32 pageAddr, u8 writeNum);
static u8   flashreadStatusCom( void );
static void flashWriteEnable( void );
static void flashRead(u8 *buff, u32 addr, u32 readNum);
uint8 spiReadByte( void );
void spiSendByte( u8 byteValue );  
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count		/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}

static int MMC_disk_status()
{
  return 1;
}
/*
 * ��ʼ��SPI:
 * �ȷ���MSB,
 * ������2��Ƶ,
 * ��ģʽ,
 * ����״̬SCK���ֵ�,
 * ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ,
 * ˫�ߵ�������ģʽ,
 * ��ֹ������豸����,
 * crcУ��0x00
 */
static int MMC_disk_initialize()
{
  //��ʼ��SPI IO��
  GPIO_Init(CS_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);  
  GPIO_Init(SPI_SCK_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);  
  GPIO_Init(SPI_MOSI_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);  
  GPIO_Init(SPI_MISO_PIN,GPIO_MODE_IN_PU_NO_IT);
  //��ʼ��SPI
  SPI_DeInit(); 
  SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00);
  SPI_Cmd(TRUE); 
  return 1;
}
static int MMC_disk_write(const BYTE *buff, DWORD sector, UINT count)
{
	u32 sectorAddr=0;
	//�ȴ�STATUS_WIPΪ0 busy�ж�
	while (flashreadStatusCom()&STATUS_WIP){
		u8 timeout=255;
		if (timeout--)break;
		return 0;
	}
	//����дʹ������
	flashWriteEnable();
	
	BYTE      *buf    = (u8*)buff;       
	u32  sectorAddr   = ((u32)sector) << 12;
	
	for(i=0; i < count; i++)  {   
		SPI_Flash_Erase_Sector(sector);    
		sector ++;    
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;       
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;       
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;       
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;   
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;    
		flashWritePage((u8*)buf, sectorAddr, 256);buf += 256;sectorAddr += 256;        
	}
	
  return RES_OK;
}

static int MMC_disk_read(BYTE *buff, DWORD sector, UINT count)
{
	flashRead(buff, ((u32)sector) << 12, ((u32)count) << 12);    
	return RES_OK; 
}

static u8 flashEraseSector(u32 sector)
{
	u32  sectorAddr = ((u32)sector << 12);
	//�ȴ�STATUS_WIPΪ0 busy�ж�
	while (flashreadStatusCom()&STATUS_WIP){
		u8 timeout=255;
		if (timeout--)break;
		return 0;
	}
  flashWriteEnable();                                                           //����дʹ��
  FILECS_LOW;                                                                   //ʹ���豸

  spiSendByte(sectorEraCom);                                                		//��������
  spiSendByte((u8)(sectorAddr>>16));                                            //���͵�ַ
  spiSendByte((u8)(sectorAddr>>8));                                             //���͵�ַ
  spiSendByte((u8)(sectorAddr));                                                //���͵�ַ

  FILECS_HIGH;                                                                  //�����豸
  return 0x01;
}

static void flashWritePage(u8 *buf, u32 pageAddr, u8 writeNum)
{
	FILECS_LOW;                                                                  //ʹ���豸
	
	spiSendByte(pageProCom);                                                     //����д��������
  spiSendByte((u8)(pageAddr>>16));                                             //���͵�ַ
  spiSendByte((u8)(pageAddr>>8));                                              //���͵�ַ
  spiSendByte((u8)(pageAddr));                                                 //���͵�ַ
	
	for (u8 i=0, i<writeNum; i++){
		spiSendByte(*buf);																												 //���ݷ���
		buf++;
	}
	FILECS_HIGH;
}

static unsigned char8 flashreadStatusCom( void )
{
  unsigned char8 status;
  FILECS_LOW;                                                                   //ʹ���豸

  spiSendByte(readStatusCom);                                                   //��״̬�Ĵ���
  status = spiReadByte();                                                       //ȡ�÷��ص�����

  FILECS_HIGH;                                                                  //�����豸
  return status;
}

static void flashWriteEnable( void )
{
	FILECS_LOW;                                                                   //ʹ���豸
  spiSendByte(writeEnCom);                                                  //�����
  FILECS_HIGH;                                                                  //�����豸
}

static void flashRead(u8 *buff, u32 addr, u32 readNum)
{
	//�ȴ�STATUS_WIPΪ0 busy�ж�
	while (flashreadStatusCom()&STATUS_WIP){
		u8 timeout=255;
		if (timeout--)break;
		return 0;
	}
	
  FILECS_LOW;                                                                   //ʹ���豸

  MCU_SPISend(readDataCom);                                                     //���Ͷ���������
  spiSendByte((u8)(addr>>16));                                                  //���͵�ַ
  spiSendByte((u8)(addr>>8));                                               		//���͵�ַ
  spiSendByte((u8)(addr));                                                 			//���͵�ַ
	for (u32 i=0; i<readNum; i++){
		*buff=spiReadByte();
		buff++;
	}
	
	FILECS_HIGH;   
}

u8 spiReadByte( void )
{
  uint8 data_buf;  
	//�����ȶ�ȡһ��,��ֹ���ջ����д�������
  data_buf = SPI_ReceiveData();  
  
  spiSendByte( 0x00 );  
  while(SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);  
  data_buf = SPI_ReceiveData(); 
	return 	data_buf;
}

void spiSendByte( u8 byteValue )  
{  
  while(SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);  
  SPI_SendData(byteValue);
}

static int RAM_disk_status()
{
  return 1;
}
static int RAM_disk_initialize()
{
  return 1;
}
static int RAM_disk_write(const BYTE *buff, DWORD sector, UINT count)
{
  return 1;
}
static int RAM_disk_read(BYTE *buff, DWORD sector, UINT count)
{
  return 1;
}

static int USB_disk_status()
{
  return 1;
}
static int USB_disk_initialize()
{
  return 1;
}
static int USB_disk_write(const BYTE *buff, DWORD sector, UINT count)
{
  return 1;
}
static int USB_disk_read(BYTE *buff, DWORD sector, UINT count)
{
  return 1;
}
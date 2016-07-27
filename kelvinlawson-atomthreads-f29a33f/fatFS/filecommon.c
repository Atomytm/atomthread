#include "ff.h"
#include "stdio.h"
#include "stm8s.h"
void printFile(FIL *file);
FRESULT fileFormat(BYTE * work,uint32_t worksize);

void printFile(FIL *file)
{
  u8 readByte;
  UINT bw;
  int32_t a;
  f_lseek(file, 0);
  a=f_size(file);
  printf ("�ļ���С %ld\r\n",a);
  while (!(f_eof(file))){
    f_read(file, &readByte, 1, &bw);
    printf("%c",readByte);
  }
  printf("\r\n");  
  f_lseek(file, 0);
}

//��Ҫ_MAX_SS�ڴ�
FRESULT fileFormat(BYTE * work,uint32_t worksize)
{
  
  FRESULT res;
  FATFS fs;           /* File system object */
  
  res=f_mount(&fs, "", 1);
  if (res != FR_OK)
	{
		printf("�������: %u\r\n",res);
	}	
  printf("��ʼ��ʽ��...\r\n");
  
  res = f_mkfs( "", FM_ANY|FM_SFD, 1024, work, worksize);
  if (res == FR_OK)
  {
    printf("��ʽ���ɹ�...\r\n");
  }
  else
  {
    printf("��ʽ��ʧ��...\r\n");
    printf("�������: %u\r\n",res);
  }
  f_mount(0, "", 1);
  
  return res;
}
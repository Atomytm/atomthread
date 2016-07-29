#include "ff.h"
#include "stdio.h"
#include "stm8s.h"
#include "string.h"
void printFile(FIL *file);
FRESULT fileFormat(BYTE * work,uint32_t worksize);
FRESULT scan_files (char* path);

void printFile(FIL *file)
{
  u8 readByte;
  UINT bw;
  int32_t a;
  f_lseek(file, 0);
  a=f_size(file);
  printf ("�ļ���С %ld\n",a);
  while (!(f_eof(file))){
    f_read(file, &readByte, 1, &bw);
    printf("%c",readByte);
  }
  printf("\n");  
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

FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;

    res = f_opendir(&dir, path);                         //Open the directory
    if (res == FR_OK) {
      for (;;) {
          res = f_readdir(&dir, &fno);                   // Read a directory item 
          if (res != FR_OK || fno.fname[0] == 0) break;  // Break on error or end of dir 
          i = strlen(path);
          if (i!=1)
          printf("%s/%s\n",path,fno.fname);
          else 
          printf("%s%s\n",path,fno.fname);
          if (fno.fattrib & AM_DIR) {                    // It is a directory 
              sprintf(&path[i], "/%s", fno.fname);
              res = scan_files(path);                    // Enter the directory 
              if (res != FR_OK) break;
              path[i] = 0;
          } else {                                       // It is a file. 

          }
      }
      f_closedir(&dir);    
    }
    return res;
}
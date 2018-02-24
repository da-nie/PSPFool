#include "video.h"

SVideo_DisplaySetting sVideo_DisplaySetting;

void Video_InitDisplay(void)
{
 //переходим в графический режим
 sceDisplaySetMode(0,480,272);
 //устанавливаем адрес видеопамяти
 unsigned char *vram_begin=(unsigned char*)(0x44000000);//адрес видеопамяти
 sceDisplaySetFrameBuf((void*)vram_begin,512,PSP_DISPLAY_PIXEL_FORMAT_8888,PSP_DISPLAY_SETBUF_NEXTFRAME);
 sceDisplayWaitVblankStart();
 sVideo_DisplaySetting.ScreenWidth=480;
 sVideo_DisplaySetting.ScreenHeight=272;
 sVideo_DisplaySetting.LineWidth=512;
 sVideo_DisplaySetting.VPtr=vram_begin;
 sVideo_DisplaySetting.DVPtr=sVideo_DisplaySetting.LineWidth*4;
 sVideo_DisplaySetting.ActivePage=0;
}
void Video_SetDisplayPage(int page)
{
 sVideo_DisplaySetting.VPtr=(unsigned char*)(0x44000000+480*512*4*page);//адрес видеопамяти
 sVideo_DisplaySetting.ActivePage=page;
}
void Video_ViewDisplayPage(void)
{
 sceDisplaySetFrameBuf((void*)sVideo_DisplaySetting.VPtr,512,PSP_DISPLAY_PIXEL_FORMAT_8888,PSP_DISPLAY_SETBUF_IMMEDIATE);
 sceDisplayWaitVblankStart();
}
void Video_ChangeDisplayPage(void)
{
 sVideo_DisplaySetting.ActivePage++;
 sVideo_DisplaySetting.ActivePage%=2;
 sVideo_DisplaySetting.VPtr=(unsigned char*)(0x44000000+480*512*4*sVideo_DisplaySetting.ActivePage);//адрес видеопамяти
}
void Video_ClearScreen(void)
{
 memset(sVideo_DisplaySetting.VPtr,0,sVideo_DisplaySetting.ScreenHeight*sVideo_DisplaySetting.LineWidth*4);
}
bool Video_SaveScreenAsTGA(char *FileName)
{
 struct TGAHEADER tgaHeader;
 tgaHeader.identsize=0;
 tgaHeader.colorMapType=0;
 tgaHeader.imageType=2;
 tgaHeader.colorMapStart=0;
 tgaHeader.colorMapLength=0;
 tgaHeader.colorMapBits=24;
 tgaHeader.xstart=0;
 tgaHeader.ystart=0;
 tgaHeader.width=sVideo_DisplaySetting.ScreenWidth;
 tgaHeader.height=sVideo_DisplaySetting.ScreenHeight;
 tgaHeader.bits=24;
 tgaHeader.descriptor=32;
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_WRONLY|PSP_O_CREAT,0777);//открываем файл
 //сохраняем заголовок
 if (sceIoWrite(SceUID_File,&tgaHeader,sizeof(struct TGAHEADER))<(int)sizeof(struct TGAHEADER))//ошибка записи
 {
  sceIoClose(SceUID_File);
  return(false);
 }
 //переносим картинку из видеобуфера в обычную память
 unsigned char *buffer=(unsigned char*)malloc(sVideo_DisplaySetting.ScreenWidth*sVideo_DisplaySetting.ScreenHeight*3);
 int x,y;
 unsigned char *bptr=buffer;
 unsigned char *vptr=sVideo_DisplaySetting.VPtr;
 for (y=0;y<sVideo_DisplaySetting.ScreenHeight;y++,vptr+=sVideo_DisplaySetting.DVPtr)
 {
  unsigned char *vptr_l=vptr;
  for (x=0;x<sVideo_DisplaySetting.ScreenWidth;x++)
  {
   unsigned char r=*vptr_l;vptr_l++;
   unsigned char g=*vptr_l;vptr_l++;
   unsigned char b=*vptr_l;vptr_l++;
   vptr_l++;
   *bptr=b;bptr++;
   *bptr=g;bptr++;
   *bptr=r;bptr++;
  }
 }
 //сохраняем в файл
 if (sceIoWrite(SceUID_File,buffer,sVideo_DisplaySetting.ScreenWidth*sVideo_DisplaySetting.ScreenHeight*3)<sVideo_DisplaySetting.ScreenWidth*sVideo_DisplaySetting.ScreenHeight*3)//ошибка записи
 {
  free(buffer);
  sceIoClose(SceUID_File);
  return(false);
 }
 //закрываем файл
 free(buffer);
 sceIoClose(SceUID_File);
 return(true);
}


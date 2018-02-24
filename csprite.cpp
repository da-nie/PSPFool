#include "video.h"
#include "csprite.h"

extern SVideo_DisplaySetting sVideo_DisplaySetting;

//конструктор
CSprite::CSprite(void)
{
 Width=0;
 Height=0;
 Data=NULL;
 LineLength=0;
}
//деструктор
CSprite::~CSprite()
{
 Release();
}
//загрузить спрайт
bool CSprite::Load(char *FileName)
{
 Release();
 //пробуем считать изображение
 TGAHEADER tgaHeader;
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//открываем файл
 if (SceUID_File<0) return(false);//ошибка
 //читаем заголовок
 if (sceIoRead(SceUID_File,&tgaHeader,sizeof(TGAHEADER))<(int)sizeof(TGAHEADER))//ошибка - мало данных
 {
  sceIoClose(SceUID_File);
  return(false);
 }
 //проверяем на возможность чтения
 if (tgaHeader.imageType&8)
 {
  sceIoClose(SceUID_File);
  return(false);//RLE не поддерживаем
 }
 if ((tgaHeader.imageType&7)==0 || (tgaHeader.imageType&7)==3)
 {
  sceIoClose(SceUID_File);
  return(false);//градации серого и отсутствие изображения не поддерживаем
 }
 //задаём параметры изображения
 Width=tgaHeader.width;
 Height=tgaHeader.height;
 LineLength=tgaHeader.width*4;
 //выделяем память для изображения
 int image_length=tgaHeader.width*tgaHeader.height*tgaHeader.bits/8;
 unsigned char *i_buffer=(unsigned char*)malloc(image_length);
 //считываем изображение
 sceIoLseek(SceUID_File,sizeof(struct TGAHEADER)+tgaHeader.colorMapStart+tgaHeader.colorMapLength*tgaHeader.colorMapBits/8,SEEK_SET);
 if(sceIoRead(SceUID_File,i_buffer,image_length)<image_length)
 {
  sceIoClose(SceUID_File);
  free(i_buffer);
  return(false);
 }
 //а теперь анализируем формат
 if (tgaHeader.bits==24)//BGR - модицифируем для четвёрок байт
 {
  sceIoClose(SceUID_File);
  unsigned char *out_image=(unsigned char*)malloc(tgaHeader.width*tgaHeader.height*4);
  int y,x;
  if (tgaHeader.descriptor==32)//прямой формат
  {
   unsigned char *oi_ptr=out_image;
   unsigned char *i_ptr=i_buffer;
   for(y=0;y<tgaHeader.height;y++,i_ptr+=tgaHeader.width*3)
   {
    unsigned char *i_ptrc=i_ptr;
    for(x=0;x<tgaHeader.width;x++)
    {
     unsigned char b=*(i_ptrc);i_ptrc++;
     unsigned char g=*(i_ptrc);i_ptrc++;
     unsigned char r=*(i_ptrc);i_ptrc++;
     unsigned char a=1;
     *oi_ptr=r;oi_ptr++;
     *oi_ptr=g;oi_ptr++;
     *oi_ptr=b;oi_ptr++;
     *oi_ptr=a;oi_ptr++;
    }
   }
  }
  if (tgaHeader.descriptor==8)//обратный формат
  {
   unsigned char *oi_ptr=out_image;
   unsigned char *i_ptr=i_buffer+tgaHeader.width*tgaHeader.height*3-1;
   for(y=tgaHeader.height-1;y>=0;y--,i_ptr-=tgaHeader.width*3)
   {
    unsigned char *i_ptrc=i_ptr;
    for(x=0;x<tgaHeader.width;x++)
    {
     unsigned char b=*(i_ptrc);i_ptrc++;
     unsigned char g=*(i_ptrc);i_ptrc++;
     unsigned char r=*(i_ptrc);i_ptrc++;
     unsigned char a=1;
     *oi_ptr=r;oi_ptr++;
     *oi_ptr=g;oi_ptr++;
     *oi_ptr=b;oi_ptr++;
     *oi_ptr=a;oi_ptr++;
    }
   }
  }
  free(i_buffer);
  Data=out_image;
  return(true);
 }
 if (tgaHeader.colorMapType==1 && tgaHeader.colorMapBits/8==3)//есть палитра по 24 бита
 {
  sceIoLseek(SceUID_File,tgaHeader.colorMapStart+sizeof(struct TGAHEADER),SEEK_SET);
  //читаем палитру
  unsigned char *color_map=(unsigned char*)malloc(tgaHeader.colorMapLength*3);
  if (sceIoRead(SceUID_File,color_map,tgaHeader.colorMapLength*3)<tgaHeader.colorMapLength*3)
  {
   sceIoClose(SceUID_File);
   free(color_map);
   free(i_buffer);
   return(false);
  }
  //нам потребуется изменить формат
  unsigned char *out_image=(unsigned char*)malloc(tgaHeader.width*tgaHeader.height*4);
  int y,x;
  if (tgaHeader.descriptor==32)//прямой формат
  {
   unsigned char *oi_ptr=out_image;
   unsigned char *i_ptr=i_buffer;
   for(y=0;y<tgaHeader.height;y++,i_ptr+=tgaHeader.width)
   {
    unsigned char *i_ptrc=i_ptr;
    for(x=0;x<tgaHeader.width;x++,i_ptrc++)
    {
     int index=(*i_ptrc)*3;
     unsigned char b=color_map[index];
     unsigned char g=color_map[index+1];
     unsigned char r=color_map[index+2];
     unsigned char a=1;
     *oi_ptr=r;oi_ptr++;
     *oi_ptr=g;oi_ptr++;
     *oi_ptr=b;oi_ptr++;
     *oi_ptr=a;oi_ptr++;
    }
   }
  }
  if (tgaHeader.descriptor==8)//формат перевёрнутый
  {
   unsigned char *oi_ptr=out_image;
   unsigned char *i_ptr=i_buffer+tgaHeader.width*(tgaHeader.height-1);
   for(y=tgaHeader.height-1;y>=0;y--,i_ptr-=tgaHeader.width)
   {
    unsigned char *i_ptrc=i_ptr;
    for(x=0;x<tgaHeader.width;x++,i_ptrc++)
    {
     int index=(*i_ptrc)*3;
     unsigned char b=color_map[index];
     unsigned char g=color_map[index+1];
     unsigned char r=color_map[index+2];
     unsigned char a=1;
     *oi_ptr=r;oi_ptr++;
     *oi_ptr=g;oi_ptr++;
     *oi_ptr=b;oi_ptr++;
     *oi_ptr=a;oi_ptr++;
    }
   }
  }
  free(i_buffer);
  free(color_map);
  Data=out_image;
  sceIoClose(SceUID_File);
  return(true);
 }
 //иные режимы не поддерживаем
 sceIoClose(SceUID_File);
 free(i_buffer);
 return(false);
}
//отобразить спрайт
void CSprite::Put(int x,int y,bool alpha)
{
 if (Data==NULL || Width==0 || Height==0) return;//спрайт отсутствует
 int x1=x;
 int x2=x+Width;
 int y1=y;
 int y2=y+Height;
 if (x2<0) return;//не видим
 if (y2<0) return;//не видим
 if (x1>sVideo_DisplaySetting.ScreenWidth) return;//не видим
 if (y1>sVideo_DisplaySetting.ScreenHeight) return;//не видим
 //обрезаем по границам экрана
 if (x1<0) x1=0;
 if (x2>sVideo_DisplaySetting.ScreenWidth) x2=sVideo_DisplaySetting.ScreenWidth;
 if (y1<0) y1=0;
 if (y2>sVideo_DisplaySetting.ScreenHeight) y2=sVideo_DisplaySetting.ScreenHeight;
 int ly,lx;
 unsigned char *s_ptr=Data+((x1-x)+(y1-y)*Width)*4;
 unsigned char *v_ptr=sVideo_DisplaySetting.VPtr+(x1+y1*sVideo_DisplaySetting.LineWidth)*4;
 int dv_ptr=sVideo_DisplaySetting.DVPtr;
 int ds_ptr=LineLength;
 if (alpha==false)
 {
  int length=(x2-x1)*4;
  for(ly=y1;ly<y2;ly++,v_ptr+=dv_ptr,s_ptr+=ds_ptr) memcpy(v_ptr,s_ptr,length);
 }
 else
 {
  int length=x2-x1;
  for(ly=y1;ly<y2;ly++,v_ptr+=dv_ptr,s_ptr+=ds_ptr)
  {
   unsigned char *s_ptr_l=s_ptr;
   unsigned char *v_ptr_l=v_ptr;
   for(lx=0;lx<length;lx++)
   {
    unsigned char r=*s_ptr_l;s_ptr_l++;
    unsigned char g=*s_ptr_l;s_ptr_l++;
    unsigned char b=*s_ptr_l;s_ptr_l++;
    unsigned char a=*s_ptr_l;s_ptr_l++;
    if (a!=0)
    {
     *v_ptr_l=r;v_ptr_l++;
     *v_ptr_l=g;v_ptr_l++;
     *v_ptr_l=b;v_ptr_l++;
     v_ptr_l++;
    }
    else v_ptr_l+=4;
   }
  }
 }
}
//отобразить часть спрайта
void CSprite::PutSpriteItem(int x,int y,int offsetx,int offsety,int width,int height,bool alpha)
{
 if (Data==NULL || Width==0 || Height==0) return;//спрайт отсутствует
 int x1=x;
 int x2=x+width;
 int y1=y;
 int y2=y+height;
 if (x2<0) return;//не видим
 if (y2<0) return;//не видим
 if (x1>sVideo_DisplaySetting.ScreenWidth) return;//не видим
 if (y1>sVideo_DisplaySetting.ScreenHeight) return;//не видим
 //обрезаем по границам экрана
 if (x1<0) x1=0;
 if (x2>sVideo_DisplaySetting.ScreenWidth) x2=sVideo_DisplaySetting.ScreenWidth;
 if (y1<0) y1=0;
 if (y2>sVideo_DisplaySetting.ScreenHeight) y2=sVideo_DisplaySetting.ScreenHeight;
 int ly,lx;
 unsigned char *s_ptr=Data+((offsetx+(x1-x))+(offsety+(y1-y))*Width)*4;
 unsigned char *v_ptr=sVideo_DisplaySetting.VPtr+(x1+y1*sVideo_DisplaySetting.LineWidth)*4;
 int dv_ptr=sVideo_DisplaySetting.DVPtr;
 int ds_ptr=LineLength;
 if (alpha==false)
 {
  int length=(x2-x1)*4;
  for(ly=y1;ly<y2;ly++,v_ptr+=dv_ptr,s_ptr+=ds_ptr) memcpy(v_ptr,s_ptr,length);
 }
 else
 {
  int length=x2-x1;
  for(ly=y1;ly<y2;ly++,v_ptr+=dv_ptr,s_ptr+=ds_ptr)
  {
   unsigned char *s_ptr_l=s_ptr;
   unsigned char *v_ptr_l=v_ptr;
   for(lx=0;lx<length;lx++)
   {
    unsigned char r=*s_ptr_l;s_ptr_l++;
    unsigned char g=*s_ptr_l;s_ptr_l++;
    unsigned char b=*s_ptr_l;s_ptr_l++;
    unsigned char a=*s_ptr_l;s_ptr_l++;
    if (a!=0)
    {
     *v_ptr_l=r;v_ptr_l++;
     *v_ptr_l=g;v_ptr_l++;
     *v_ptr_l=b;v_ptr_l++;
     v_ptr_l++;
    }
    else v_ptr_l+=4;
   }
  }
 }
}
void CSprite::PutSpriteItemMask(int x,int y,int offsetx,int offsety,int width,int height,unsigned char *Mask)
{
 if (Data==NULL || Width==0 || Height==0 || Mask==NULL) return;//спрайт или маска спрайта отсутствует
 int x1=x;
 int x2=x+width;
 int y1=y;
 int y2=y+height;
 if (x2<0) return;//не видим
 if (y2<0) return;//не видим
 if (x1>sVideo_DisplaySetting.ScreenWidth) return;//не видим
 if (y1>sVideo_DisplaySetting.ScreenHeight) return;//не видим
 //обрезаем по границам экрана
 if (x1<0) x1=0;
 if (x2>sVideo_DisplaySetting.ScreenWidth) x2=sVideo_DisplaySetting.ScreenWidth;
 if (y1<0) y1=0;
 if (y2>sVideo_DisplaySetting.ScreenHeight) y2=sVideo_DisplaySetting.ScreenHeight;
 int ly,lx;
 unsigned char *m_ptr=Mask;
 unsigned char *s_ptr=Data+((offsetx+(x1-x))+(offsety+(y1-y))*Width)*4;
 unsigned char *v_ptr=sVideo_DisplaySetting.VPtr+(x1+y1*sVideo_DisplaySetting.LineWidth)*4;
 int dm_ptr=width;
 int dv_ptr=sVideo_DisplaySetting.DVPtr;
 int ds_ptr=LineLength;
 int length=x2-x1;
 for(ly=y1;ly<y2;ly++,v_ptr+=dv_ptr,s_ptr+=ds_ptr,m_ptr+=dm_ptr)
 {
  unsigned char *m_ptr_l=m_ptr;
  unsigned char *s_ptr_l=s_ptr;
  unsigned char *v_ptr_l=v_ptr;
  for(lx=0;lx<length;lx++)
  {
   unsigned char r=*s_ptr_l;s_ptr_l++;
   unsigned char g=*s_ptr_l;s_ptr_l++;
   unsigned char b=*s_ptr_l;s_ptr_l++;
   s_ptr_l++;
   unsigned char m=*m_ptr_l;m_ptr_l++;
   if (m!=0)
   {
    *v_ptr_l=r;v_ptr_l++;
    *v_ptr_l=g;v_ptr_l++;
    *v_ptr_l=b;v_ptr_l++;
    v_ptr_l++;
   }
   else v_ptr_l+=4;
  }
 }
}
void CSprite::SetAlpha(unsigned char alpha,unsigned char r,unsigned char g,unsigned char b)
{
 if (Data==NULL || Width==0 || Height==0) return;//спрайт отсутствует
 unsigned char *ptr=Data;
 int n;
 int length=Width*Height;
 for(n=0;n<length;n++)
 {
  unsigned char ri=*ptr;ptr++;
  unsigned char gi=*ptr;ptr++;
  unsigned char bi=*ptr;ptr++;
  if (ri==r && gi==g && bi==b) *ptr=alpha;
  ptr++;
 }
}
void CSprite::Release(void)
{
 if (Data!=NULL) free(Data);
 Data=NULL;
 Width=0;
 Height=0;
 LineLength=0;
}
int CSprite::GetWidth(void)
{
 return(Width);
}
int CSprite::GetHeight(void)
{
 return(Height);
}

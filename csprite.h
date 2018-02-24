#ifndef CSPRITE_H_INCLUDED
#define CSPRITE_H_INCLUDED

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//спрайт
class CSprite
{
 protected:
  int Width;//ширина
  int Height;//высота
  unsigned char *Data;//указатель на данные спрайта
  int LineLength;//размер строки в байтах
 public:
  CSprite(void);//конструктор
  ~CSprite();//деструктор
  bool Load(char *FileName);//загрузить спрайт
  void Put(int x,int y,bool alpha);//отобразить спрайт
  void PutSpriteItem(int x,int y,int offsetx,int offsety,int width,int height,bool alpha);//отобразить часть спрайта
  void PutSpriteItemMask(int x,int y,int offsetx,int offsety,int width,int height,unsigned char *Mask);//отобразить часть спрайта с маской
  void SetAlpha(unsigned char alpha,unsigned char r,unsigned char g,unsigned char b);//установить значение програчности
  void Release(void);//удалить спрайт
  int GetWidth(void);//получить ширину спрайта
  int GetHeight(void);//получить высоту спрайта
};
#endif

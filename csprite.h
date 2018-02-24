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

//������
class CSprite
{
 protected:
  int Width;//������
  int Height;//������
  unsigned char *Data;//��������� �� ������ �������
  int LineLength;//������ ������ � ������
 public:
  CSprite(void);//�����������
  ~CSprite();//����������
  bool Load(char *FileName);//��������� ������
  void Put(int x,int y,bool alpha);//���������� ������
  void PutSpriteItem(int x,int y,int offsetx,int offsety,int width,int height,bool alpha);//���������� ����� �������
  void PutSpriteItemMask(int x,int y,int offsetx,int offsety,int width,int height,unsigned char *Mask);//���������� ����� ������� � ������
  void SetAlpha(unsigned char alpha,unsigned char r,unsigned char g,unsigned char b);//���������� �������� ������������
  void Release(void);//������� ������
  int GetWidth(void);//�������� ������ �������
  int GetHeight(void);//�������� ������ �������
};
#endif

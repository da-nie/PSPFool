#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//��������� TGA-�����
#pragma pack(1)
struct TGAHEADER
{
 char identsize;//������ ���� ID ��������� (0)
 char colorMapType;//���� �� �������:0-���,1-����
 char imageType;//��� ��������:0-���,1-��������� �����,2-RGB,3-������� ������, (3-� ��� - RLE-�����������)
 unsigned short	colorMapStart;//������ ����� ������
 unsigned short	colorMapLength;//���������� ������ � �����
 unsigned char 	colorMapBits;//����������� �������
 unsigned short	xstart;//��������� ���������� �����������
 unsigned short	ystart;
 unsigned short	width;//������ ����������� �� X
 unsigned short	height;//������ ����������� �� Y
 char bits;//��������� ��� �� ������� (8,16,24,32)
 char descriptor;//���������� ������������
};
#pragma pack(8)

//��������� ������
struct SVideo_DisplaySetting
{
 int ScreenWidth;//������ ������
 int ScreenHeight;//������ ������
 int LineWidth;//����� �����
 unsigned char *VPtr;//��������� �� ����������
 int DVPtr;//��������� ������ ��� �������� �� y
 int ActivePage;//�������� �������� (�� ��� ��������� ���, �� ��� ������������� �������)
};

//���������������� ����������� �������
void Video_InitDisplay(void);
//���������� �������� �����������
void Video_SetDisplayPage(int page);
//������� �������� ����������� ������������
void Video_ViewDisplayPage(void);
//������� �������������
void Video_ChangeDisplayPage(void);
//�������� �����
void Video_ClearScreen(void);
//��������� ����� � TGA-�����
bool Video_SaveScreenAsTGA(char *FileName);

#endif // VIDEO_H_INCLUDED

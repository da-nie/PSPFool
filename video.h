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

//заголовок TGA-файла
#pragma pack(1)
struct TGAHEADER
{
 char identsize;//размер поля ID заголовка (0)
 char colorMapType;//если ли палитра:0-нет,1-есть
 char imageType;//тип картинки:0-нет,1-индексные цвета,2-RGB,3-оттенки серого, (3-й бит - RLE-кодирование)
 unsigned short	colorMapStart;//начало карты цветов
 unsigned short	colorMapLength;//количество цветов в карте
 unsigned char 	colorMapBits;//размерность палитры
 unsigned short	xstart;//начальные координаты изображения
 unsigned short	ystart;
 unsigned short	width;//размер изображения по X
 unsigned short	height;//размер изображения по Y
 char bits;//количесто бит на пиксель (8,16,24,32)
 char descriptor;//дескриптор изрображения
};
#pragma pack(8)

//настройки экрана
struct SVideo_DisplaySetting
{
 int ScreenWidth;//ширина экрана
 int ScreenHeight;//высота экрана
 int LineWidth;//длина линии
 unsigned char *VPtr;//указатель на видеобуфер
 int DVPtr;//изменение адреса при переходе по y
 int ActivePage;//активная страница (на ней рисование идёт, но она необязательно видимая)
};

//инициализировать графический дисплей
void Video_InitDisplay(void);
//установить страницу видеопамяти
void Video_SetDisplayPage(int page);
//сделать страницу видеопамяти отображаемой
void Video_ViewDisplayPage(void);
//сменить видеостраницу
void Video_ChangeDisplayPage(void);
//очистить экран
void Video_ClearScreen(void);
//сохранить экран в TGA-файле
bool Video_SaveScreenAsTGA(char *FileName);

#endif // VIDEO_H_INCLUDED

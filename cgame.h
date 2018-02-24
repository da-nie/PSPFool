#ifndef CGAME_H_INCLUDED
#define CGAME_H_INCLUDED

#include "csprite.h"
#include "ccardkit.h"

class CGame
{
 protected:
  CSprite cSprite_MessageStart;//сообщение "нажмите клавишу старт"
  CSprite cSprite_MessageOk;//сообщение "бито"
  CSprite cSprite_MessageGet;//сообщение "беру"
  CSprite cSprite_MessageGetAdd;//сообщение "беру, подкидывайте"
  CSprite cSprite_MessageWinPSP;//сообщение "выиграл компьютер"
  CSprite cSprite_MessageWinPlayer;//сообщение "выиграл игрок"
  CSprite cSprite_MessageParitat;//сообщение "ничья"
  CSprite cSprite_CardValue[2][9];//значения карт:от 6 до туза
  CSprite cSprite_CardSuit[2][4];//масти карт
  CSprite cSprite_CardFront;//передняя сторона карты
  CSprite cSprite_CardBack;//задняя сторона карты
  CSprite cSprite_Pointer;//указатель на карту
  CSprite cSprite_Get;//картинка "взять"
  CSprite cSprite_Ok;//картинка "бито"
  CSprite cSprite_Fone;//картинка фона
  CCardKit cCardKit_Shop;//колода
  CCardKit cCardKit_PSP;//компьютер
  CCardKit cCardKit_Player;//игрок
  CCardKit cCardKit_TablePlayer1;//игровой стол первого игрока
  CCardKit cCardKit_TablePlayer2;//игровой стол второго игрока
  CCardKit cCardKit_KnowPlayer;//известные нам карты игрока
  SCard sCard_Main;//карта-козырь
  int Move;//текущий ход
  //-----------------------------------------------------------
 public:

  CGame(void);
  ~CGame();
  //-----------------------------------------------------------
  void Create(char *Path);
  void Release(void);
  //-----------------------------------------------------------
  void Activate(char *Path);
  //-----------------------------------------------------------
 protected:
  void SaveScreenShot(char *Path);//сохранить скриншот
  int RND(int max);//получить случайное число
  void DrawCard(int x,int y,int Suit,int Value);//нарисовать карту
  void InitKit(void);//инициализация набора карт
  void PutKit(bool psp_show);//нарисовать все отображаемые наборы карт
  int GetPlayerCard(bool PlayerMove,char *Path);//выбор игроком карты
  int GetPSPCard(bool PSPMove);//выбор компьютером карты
  int PSPOtherMove(void);//компьютер делает не первый ход
  int PSPFirstMove(void);//компьютер делает первый ход
  int PSPAnswer(void);//компьютер отбивается

  bool AddShopCard(CCardKit &cCardKit);//добавить к набору произвольные карты из колоды
  bool PlayerAddCard(char *Path);//игрок подкидывает карты
  void PSPAddCard(void);//PSP подкидывает карты
  int MoveProcessing(bool PSPMove,char *Path);//выполнить ход

  bool CheckRule(SCard sCardTable,SCard sCard);//проверить правила
  int GetPrice(SCard sCard);//получить стоимость карты
  int GetStatusCard(SCard sCard);//получить статус карты:0-плохая, 1-средняя, 2-хорошая
  int CheckEndGame(void);//проверить, не конец ли игры
  int GetKitStatus(CCardKit *cCardKit);//определить качество расклада:0-плохой, 1-средний, 2-хороший
  void PutMessage(int message);//вывести сообщение
  int SelectMove(void);//выбор первого хода
};

#endif

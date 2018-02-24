#ifndef CGAME_H_INCLUDED
#define CGAME_H_INCLUDED

#include "csprite.h"
#include "ccardkit.h"

class CGame
{
 protected:
  CSprite cSprite_MessageStart;//��������� "������� ������� �����"
  CSprite cSprite_MessageOk;//��������� "����"
  CSprite cSprite_MessageGet;//��������� "����"
  CSprite cSprite_MessageGetAdd;//��������� "����, ������������"
  CSprite cSprite_MessageWinPSP;//��������� "������� ���������"
  CSprite cSprite_MessageWinPlayer;//��������� "������� �����"
  CSprite cSprite_MessageParitat;//��������� "�����"
  CSprite cSprite_CardValue[2][9];//�������� ����:�� 6 �� ����
  CSprite cSprite_CardSuit[2][4];//����� ����
  CSprite cSprite_CardFront;//�������� ������� �����
  CSprite cSprite_CardBack;//������ ������� �����
  CSprite cSprite_Pointer;//��������� �� �����
  CSprite cSprite_Get;//�������� "�����"
  CSprite cSprite_Ok;//�������� "����"
  CSprite cSprite_Fone;//�������� ����
  CCardKit cCardKit_Shop;//������
  CCardKit cCardKit_PSP;//���������
  CCardKit cCardKit_Player;//�����
  CCardKit cCardKit_TablePlayer1;//������� ���� ������� ������
  CCardKit cCardKit_TablePlayer2;//������� ���� ������� ������
  CCardKit cCardKit_KnowPlayer;//��������� ��� ����� ������
  SCard sCard_Main;//�����-������
  int Move;//������� ���
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
  void SaveScreenShot(char *Path);//��������� ��������
  int RND(int max);//�������� ��������� �����
  void DrawCard(int x,int y,int Suit,int Value);//���������� �����
  void InitKit(void);//������������� ������ ����
  void PutKit(bool psp_show);//���������� ��� ������������ ������ ����
  int GetPlayerCard(bool PlayerMove,char *Path);//����� ������� �����
  int GetPSPCard(bool PSPMove);//����� ����������� �����
  int PSPOtherMove(void);//��������� ������ �� ������ ���
  int PSPFirstMove(void);//��������� ������ ������ ���
  int PSPAnswer(void);//��������� ����������

  bool AddShopCard(CCardKit &cCardKit);//�������� � ������ ������������ ����� �� ������
  bool PlayerAddCard(char *Path);//����� ����������� �����
  void PSPAddCard(void);//PSP ����������� �����
  int MoveProcessing(bool PSPMove,char *Path);//��������� ���

  bool CheckRule(SCard sCardTable,SCard sCard);//��������� �������
  int GetPrice(SCard sCard);//�������� ��������� �����
  int GetStatusCard(SCard sCard);//�������� ������ �����:0-������, 1-�������, 2-�������
  int CheckEndGame(void);//���������, �� ����� �� ����
  int GetKitStatus(CCardKit *cCardKit);//���������� �������� ��������:0-������, 1-�������, 2-�������
  void PutMessage(int message);//������� ���������
  int SelectMove(void);//����� ������� ����
};

#endif

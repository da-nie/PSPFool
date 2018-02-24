#ifndef CCARDKIT_H_INCLUDED
#define CCARDKIT_H_INCLUDED

struct SCard
{
 unsigned char Suit;//�����:0-4
 unsigned char Value;//�������� 6-14
};

class CCardKit
{
 protected:
  int Amount;//����� ���� � ������
  SCard *sCard_Kit;//�����
 public:
  CCardKit();
  ~CCardKit();
  void Clear(void);//�������� �����
  void PushCard(SCard sCard);//�������� ����� � �����
  SCard PopCard(void);//����� ����� �� ������
  void ChangeTwoCard(int p1,int p2);//�������� ������� ��� ����� ������
  int GetAmount(void);//�������� ���������� ���� � ������
  SCard GetCard(int index);//�������� ����� �� ������
  void DeleteCard(int index);//������� ����� �� ������
  void DeleteSCard(SCard sCard);//������� ����� �� ������

  void Add(CCardKit &cCardKit);//�������� �����
  void Sub(CCardKit &cCardKit);//������� �����
  void Copy(CCardKit &cCardKit);//������� �����
};


#endif

#ifndef CCARDKIT_H_INCLUDED
#define CCARDKIT_H_INCLUDED

struct SCard
{
 unsigned char Suit;//масть:0-4
 unsigned char Value;//значение 6-14
};

class CCardKit
{
 protected:
  int Amount;//всего карт в наборе
  SCard *sCard_Kit;//карты
 public:
  CCardKit();
  ~CCardKit();
  void Clear(void);//очистить набор
  void PushCard(SCard sCard);//положить карту в набор
  SCard PopCard(void);//взять карту из набора
  void ChangeTwoCard(int p1,int p2);//обменять местами две карты набора
  int GetAmount(void);//получить количество карт в наборе
  SCard GetCard(int index);//получить карту по номеру
  void DeleteCard(int index);//удалить карту из набора
  void DeleteSCard(SCard sCard);//удалить карту из набора

  void Add(CCardKit &cCardKit);//добавить набор
  void Sub(CCardKit &cCardKit);//вычесть набор
  void Copy(CCardKit &cCardKit);//сделать копию
};


#endif

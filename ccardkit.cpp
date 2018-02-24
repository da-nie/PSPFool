#include "ccardkit.h"

CCardKit::CCardKit()
{
 Amount=0;
 sCard_Kit=new SCard[36];
}
CCardKit::~CCardKit()
{
 delete(sCard_Kit);
}
void CCardKit::Clear(void)
{
 Amount=0;
}
void CCardKit::PushCard(SCard sCard)
{
 if (Amount>=36) return;//набор заполнен
 sCard_Kit[Amount]=sCard;
 Amount++;
}
SCard CCardKit::PopCard(void)
{
 SCard sCard;
 sCard.Value=0;
 sCard.Suit=0;
 if (Amount==0) return(sCard);//карт в наборе нет
 Amount--;
 return(sCard_Kit[Amount]);
}
void CCardKit::ChangeTwoCard(int p1,int p2)
{
 if (p1>=Amount || p2>=Amount) return;
 if (p1<0 || p2<0) return;
 SCard sCard=sCard_Kit[p1];
 sCard_Kit[p1]=sCard_Kit[p2];
 sCard_Kit[p2]=sCard;
}
int CCardKit::GetAmount(void)
{
 return(Amount);
}
SCard CCardKit::GetCard(int index)
{
 SCard sCard;
 sCard.Value=0;
 sCard.Suit=0;
 if (index>=Amount || index<0) return(sCard);//карт в наборе нет
 return(sCard_Kit[index]);
}
void CCardKit::DeleteCard(int index)
{
 if (index>=Amount || index<0) return;//карт в наборе нет
 for(int n=index;n<Amount-1;n++) sCard_Kit[n]=sCard_Kit[n+1];
 Amount--;
}
void CCardKit::DeleteSCard(SCard sCard)
{
 //ищем карту в наборе
 int n=0;
 while(n<Amount)
 {
  if (sCard_Kit[n].Suit==sCard.Suit && sCard_Kit[n].Value==sCard.Value)
  {
   DeleteCard(n);//нашли такую карту
   n=0;//начинаем поиск сначала (хотя это и не требуется на самом деле)
   continue;
  }
  n++;
 }
}
void CCardKit::Add(CCardKit &cCardKit)
{
 if (&cCardKit==this) return;
 int amount=cCardKit.GetAmount();
 for(int n=0;n<amount;n++)
 {
  SCard sCard=cCardKit.GetCard(n);
  //ищем, нет ли такой карты у нас
  bool found=false;
  for(int m=0;m<Amount;m++)
  {
   if (sCard_Kit[m].Suit==sCard.Suit && sCard_Kit[m].Value==sCard.Value)
   {
    found=true;
    break;
   }
  }
  if (found==true) continue;//такая карта уже присутствует
  PushCard(sCard);//добавляем карту
 }
}
void CCardKit::Sub(CCardKit &cCardKit)
{
 if (&cCardKit==this) return;
 int amount=cCardKit.GetAmount();
 for(int n=0;n<amount;n++)
 {
  SCard sCard=cCardKit.GetCard(n);
  DeleteSCard(sCard);//удаляем карту
 }
}
void CCardKit::Copy(CCardKit &cCardKit)
{
 Clear();
 Add(cCardKit);
}

#include <pspctrl.h>
#include <math.h>

#include "cgame.h"
#include "video.h"

#define GAME_RESTART   -1
#define GAME_OK        -2
#define GAME_GET       -3

#define MOVE_PSP     0
#define MOVE_PLAYER  1
#define MOVE_WAIT    2
#define MOVE_RESTART 3

#define END_NO      0
#define END_PARITAT 1
#define END_PSP     2
#define END_PLAYER  3

#define MESSAGE_OK         0
#define MESSAGE_GET        1
#define MESSAGE_GETADD     2
#define MESSAGE_PSP_WIN    3
#define MESSAGE_PLAYER_WIN 4
#define MESSAGE_PARITAT    5


extern bool done;
//--------------------------------------------------------------------------
CGame::CGame(void)
{
}
CGame::~CGame()
{
 Release();
}
void CGame::Create(char *Path)
{
 int n,m;

 char *FileName=new char[strlen(Path)+255];
 sprintf(FileName,"%ssprites\\6.tga",Path);
 cSprite_CardValue[0][0].Load(FileName);
 sprintf(FileName,"%ssprites\\7.tga",Path);
 cSprite_CardValue[0][1].Load(FileName);
 sprintf(FileName,"%ssprites\\8.tga",Path);
 cSprite_CardValue[0][2].Load(FileName);
 sprintf(FileName,"%ssprites\\9.tga",Path);
 cSprite_CardValue[0][3].Load(FileName);
 sprintf(FileName,"%ssprites\\10.tga",Path);
 cSprite_CardValue[0][4].Load(FileName);
 sprintf(FileName,"%ssprites\\j.tga",Path);
 cSprite_CardValue[0][5].Load(FileName);
 sprintf(FileName,"%ssprites\\q.tga",Path);
 cSprite_CardValue[0][6].Load(FileName);
 sprintf(FileName,"%ssprites\\k.tga",Path);
 cSprite_CardValue[0][7].Load(FileName);
 sprintf(FileName,"%ssprites\\a.tga",Path);
 cSprite_CardValue[0][8].Load(FileName);

 sprintf(FileName,"%ssprites\\6_i.tga",Path);
 cSprite_CardValue[1][0].Load(FileName);
 sprintf(FileName,"%ssprites\\7_i.tga",Path);
 cSprite_CardValue[1][1].Load(FileName);
 sprintf(FileName,"%ssprites\\8_i.tga",Path);
 cSprite_CardValue[1][2].Load(FileName);
 sprintf(FileName,"%ssprites\\9_i.tga",Path);
 cSprite_CardValue[1][3].Load(FileName);
 sprintf(FileName,"%ssprites\\10_i.tga",Path);
 cSprite_CardValue[1][4].Load(FileName);
 sprintf(FileName,"%ssprites\\j_i.tga",Path);
 cSprite_CardValue[1][5].Load(FileName);
 sprintf(FileName,"%ssprites\\q_i.tga",Path);
 cSprite_CardValue[1][6].Load(FileName);
 sprintf(FileName,"%ssprites\\k_i.tga",Path);
 cSprite_CardValue[1][7].Load(FileName);
 sprintf(FileName,"%ssprites\\a_i.tga",Path);
 cSprite_CardValue[1][8].Load(FileName);

 sprintf(FileName,"%ssprites\\m1.tga",Path);
 cSprite_CardSuit[0][0].Load(FileName);
 sprintf(FileName,"%ssprites\\m2.tga",Path);
 cSprite_CardSuit[0][1].Load(FileName);
 sprintf(FileName,"%ssprites\\m3.tga",Path);
 cSprite_CardSuit[0][2].Load(FileName);
 sprintf(FileName,"%ssprites\\m4.tga",Path);
 cSprite_CardSuit[0][3].Load(FileName);

 sprintf(FileName,"%ssprites\\m1_i.tga",Path);
 cSprite_CardSuit[1][0].Load(FileName);
 sprintf(FileName,"%ssprites\\m2_i.tga",Path);
 cSprite_CardSuit[1][1].Load(FileName);
 sprintf(FileName,"%ssprites\\m3_i.tga",Path);
 cSprite_CardSuit[1][2].Load(FileName);
 sprintf(FileName,"%ssprites\\m4_i.tga",Path);
 cSprite_CardSuit[1][3].Load(FileName);

 sprintf(FileName,"%ssprites\\front.tga",Path);
 cSprite_CardFront.Load(FileName);
 sprintf(FileName,"%ssprites\\back.tga",Path);
 cSprite_CardBack.Load(FileName);

 sprintf(FileName,"%ssprites\\pointer.tga",Path);
 cSprite_Pointer.Load(FileName);
 cSprite_Pointer.SetAlpha(0,0,0,0);

 sprintf(FileName,"%ssprites\\get.tga",Path);
 cSprite_Get.Load(FileName);
 sprintf(FileName,"%ssprites\\Ok.tga",Path);
 cSprite_Ok.Load(FileName);

 sprintf(FileName,"%ssprites\\message_ok.tga",Path);
 cSprite_MessageOk.Load(FileName);
 sprintf(FileName,"%ssprites\\message_get.tga",Path);
 cSprite_MessageGet.Load(FileName);
 sprintf(FileName,"%ssprites\\message_getadd.tga",Path);
 cSprite_MessageGetAdd.Load(FileName);
 sprintf(FileName,"%ssprites\\message_psp_win.tga",Path);
 cSprite_MessageWinPSP.Load(FileName);
 sprintf(FileName,"%ssprites\\message_player_win.tga",Path);
 cSprite_MessageWinPlayer.Load(FileName);
 sprintf(FileName,"%ssprites\\message_paritat.tga",Path);
 cSprite_MessageParitat.Load(FileName);
 sprintf(FileName,"%ssprites\\message_start.tga",Path);
 cSprite_MessageStart.Load(FileName);

 sprintf(FileName,"%ssprites\\fone.tga",Path);
 cSprite_Fone.Load(FileName);

 delete(FileName);
 for(n=0;n<2;n++)
 {
  for(m=0;m<4;m++) cSprite_CardSuit[n][m].SetAlpha(0,255,255,255);
  for(m=0;m<9;m++) cSprite_CardValue[n][m].SetAlpha(0,255,255,255);
 }
}
void CGame::Release(void)
{
 int n,m;
 for(n=0;n<2;n++)
 {
  for(m=0;m<4;m++) cSprite_CardSuit[n][m].Release();
  for(m=0;m<9;m++) cSprite_CardValue[n][m].Release();
 }
 cSprite_CardFront.Release();
 cSprite_CardBack.Release();
}
//--------------------------------------------------------------------------
void CGame::SaveScreenShot(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 //ищем свободную картику
 int index=1;
 while(done==false)
 {
  sprintf(FileName,"%sscreen/screen%i.tga",Path,index);
  SceUID SceUID_File;
  SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//открываем файл
  if (SceUID_File<=0) break;//такого файла нет
  sceIoClose(SceUID_File);
  index++;
 }
 Video_SaveScreenAsTGA(FileName);
 delete(FileName);
}
int CGame::RND(int max)
{
 return((int)((float)(max)*((float)rand())/((float)RAND_MAX)));
}
void CGame::DrawCard(int x,int y,int Suit,int Value)
{
 if (Value<6 || Value>14) return;//таких значений нет
 if (Suit<0 || Suit>=4) return;//таких мастей нет
 cSprite_CardFront.Put(x,y,false);//рисуем переднюю сторону карты
 //рисуем масть и значение
 Value-=6;
 //верх
 cSprite_CardValue[0][Value].Put(x+1,y+1,true);
 cSprite_CardSuit[0][Suit].Put(x+10,y+1,true);
 //середина
 cSprite_CardSuit[0][Suit].Put(x+1,y+14,true);
 cSprite_CardSuit[1][Suit].Put(x+18,y+14,true);
 //низ
 cSprite_CardSuit[1][Suit].Put(x+10,y+28,true);
 cSprite_CardValue[1][Value].Put(x+17,y+27,true);
}
void CGame::InitKit(void)
{
 int n;
 //очищаем наборы
 cCardKit_Shop.Clear();
 cCardKit_PSP.Clear();
 cCardKit_Player.Clear();
 cCardKit_TablePlayer1.Clear();
 cCardKit_TablePlayer2.Clear();
 cCardKit_KnowPlayer.Clear();
 //инициализируем колоду
 for(n=0;n<36;n++)
 {
  SCard sCard;
  sCard.Value=n%9+6;
  sCard.Suit=n/9;
  cCardKit_Shop.PushCard(sCard);
 }
 //мешаем колоду
 u64 current_tick;
 sceRtcGetCurrentTick(&current_tick);
 int value=current_tick&0xFFFFFFFF;
 srand(value);
 for(n=0;n<1000;n++)
 {
  int p1=RND(35);
  int p2=RND(35);
  cCardKit_Shop.ChangeTwoCard(p1,p2);
 }
 //сдаём карты игрокам
 for(n=0;n<6;n++)
 {
  SCard sCard;
  sCard=cCardKit_Shop.PopCard();
  cCardKit_PSP.PushCard(sCard);
  sCard=cCardKit_Shop.PopCard();
  cCardKit_Player.PushCard(sCard);
 }
 //выбираем козырную карту
 sCard_Main=cCardKit_Shop.GetCard(0);
}
void CGame::PutKit(bool show_psp)
{
 int x,y;
 int amount;
 int line;
 int current;
 SCard sCard;
 //фон
 cSprite_Fone.Put(0,0,false);
 //карты компьютера
 amount=cCardKit_PSP.GetAmount();
 line=amount/12;
 if (line*12<amount) line++;
 current=0;
 for(y=0;y<line;y++)
  for(x=0;x<12;x++,current++)
  {
   if (current>=amount) break;
   if (show_psp==true)
   {
    sCard=cCardKit_PSP.GetCard(current);
    DrawCard(10+x*30,10+y*20,sCard.Suit,sCard.Value);
   }
   else cSprite_CardBack.Put(10+x*30,10+y*20,false);//рисуем заднюю сторону карты
  }
 //карты игрока
 amount=cCardKit_Player.GetAmount();
 line=amount/12;
 if (line*12<amount) line++;
 current=0;
 for(y=0;y<line;y++)
  for(x=0;x<12;x++,current++)
  {
   if (current>=amount) break;
   sCard=cCardKit_Player.GetCard(current);
   DrawCard(10+x*30,182+y*20,sCard.Suit,sCard.Value);
  }
 //колода
 amount=cCardKit_Shop.GetAmount();
 if (amount>0)
 {
  //козырная карта
  sCard=cCardKit_Shop.GetCard(0);
  DrawCard(400,117,sCard.Suit,sCard.Value);
  //колода
  for(y=1;y<amount;y++) cSprite_CardBack.Put(420,50+y*6,false);//рисуем заднюю сторону карты
 }
 //игровое поле
 amount=cCardKit_TablePlayer1.GetAmount();
 current=0;
 for(x=0;x<6;x++,current++)
 {
  if (current>=amount) break;
  sCard=cCardKit_TablePlayer1.GetCard(current);
  DrawCard(10+x*50,110,sCard.Suit,sCard.Value);
 }
 amount=cCardKit_TablePlayer2.GetAmount();
 current=0;
 for(x=0;x<6;x++,current++)
 {
  if (current>=amount) break;
  sCard=cCardKit_TablePlayer2.GetCard(current);
  DrawCard(15+x*50,120,sCard.Suit,sCard.Value);
 }
}
void CGame::Activate(char *Path)
{
 InitKit();
 Move=MOVE_WAIT;//игра окончена
 SceCtrlData pad;
 while(done==false)
 {
  if (Move==MOVE_WAIT)//ждём клавиши начала игры
  {
   sceCtrlReadBufferPositive(&pad,1);//считываем клавиши
   if (pad.Buttons&PSP_CTRL_START) Move=MOVE_RESTART;
  }
  if (Move==MOVE_RESTART)
  {
   InitKit();
   Move=SelectMove();//определение, кто ходит первый
  }
  Video_ClearScreen();
  if (Move==MOVE_WAIT) PutKit(true);
                  else PutKit(false);
  if (Move==MOVE_WAIT) cSprite_MessageStart.Put(176,104,false);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  if (Move==MOVE_PSP)
  {
   Move=MoveProcessing(true,Path);//ходит компьютер
   continue;
  }
  if (Move==MOVE_PLAYER)
  {
   Move=MoveProcessing(false,Path);//ходит игрок
   continue;
  }
 }
}
int CGame::GetPlayerCard(bool PlayerMove,char *Path)
{
 int Pointer=0;
 SceCtrlData pad;
 int key_delay=100;
 int amount_pos=cCardKit_Player.GetAmount();
 while(done==false)
 {
  sceCtrlReadBufferPositive(&pad,1);//считываем клавиши
  bool on_key=false;
  if (key_delay>0) key_delay--;
  if (pad.Buttons&PSP_CTRL_RTRIGGER && pad.Buttons&PSP_CTRL_LTRIGGER)
  {
   SaveScreenShot(Path);
  }
  if (pad.Buttons&PSP_CTRL_START)
  {
   return(GAME_RESTART);
  }
  if (pad.Buttons&PSP_CTRL_LEFT)//нажали левую клавишу
  {
   if (key_delay==0)
   {
    Pointer--;
    if (Pointer<0) Pointer=amount_pos;
    key_delay=15;
   }
   on_key=true;
  }
  if (pad.Buttons&PSP_CTRL_RIGHT)//нажали правую клавишу
  {
   if (key_delay==0)
   {
    Pointer++;
    if (Pointer>amount_pos) Pointer=0;
    key_delay=15;
   }
   on_key=true;
  }
  if (pad.Buttons&PSP_CTRL_CROSS)//возвращаем выбранную карту
  {
   if (key_delay==0)
   {
    if (Pointer<cCardKit_Player.GetAmount()) return(Pointer);
    if (PlayerMove==false) return(GAME_GET);
    return(GAME_OK);
   }
   on_key=true;
  }
  if (on_key==false) key_delay=0;
  Video_ClearScreen();
  //рисуем карты
  PutKit(false);
  //рисуем кнопки
  if (PlayerMove==false) cSprite_Get.Put(400,240,false);
                    else cSprite_Ok.Put(400,240,false);
  //рисуем указатель на карты игрока
  if (Pointer<cCardKit_Player.GetAmount())//если указатель на картах
  {
   int x=Pointer%12;
   int y=Pointer/12;
   cSprite_Pointer.Put(10+x*30,182+y*20+5,true);
  }
  else cSprite_Pointer.Put(420,245,true);//если указатель на строчке меню
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
 }
 return(0);
}
int CGame::GetPSPCard(bool PSPMove)
{
 if (PSPMove==true)//компьютер ходит
 {
  if (cCardKit_TablePlayer1.GetAmount()!=0)//уже были произведены ходы
  {
   return(PSPOtherMove());
  }
  else//компьютер ещё не ходил
  {
   return(PSPFirstMove());//делаем первый ход
  }
 }
 else return(PSPAnswer());//компьютер отбивается
 return(GAME_GET);
}
int  CGame::PSPFirstMove(void)
{
 int n;
 //определяем наш расклад до хода
 int Status_My=GetKitStatus(&cCardKit_PSP);//оцениваем наш расклад
 //берём произвольную карту из колоды
 //делаем копию колоды
 CCardKit cCardKit_ShopCopy;
 cCardKit_ShopCopy.Copy(cCardKit_Shop);//переносим туда карты колоды
 cCardKit_ShopCopy.Add(cCardKit_Player);//переносим туда карты игрока
 cCardKit_ShopCopy.Sub(cCardKit_KnowPlayer);//убираем оттуда карты игрока, которые мы знаем
 //смотрим, сколько в колоде вообще было карт
 int shop_amount=cCardKit_Shop.GetAmount();
 int shop_card_status=2;//по-умолчанию, считаем, что в колоде придёт хорошая карта (даже если колода пустая)
 if (shop_amount>0)//если в колоде есть карты
 {
  int shop_copy_amount=cCardKit_ShopCopy.GetAmount();
  //выбираем произвольную карту
  int select_card=RND(shop_copy_amount-1);
  SCard sCard_Shop=cCardKit_ShopCopy.GetCard(select_card);
  //оцениваем её
  shop_card_status=GetStatusCard(sCard_Shop);
 }
 //а теперь создаём расклад игрока и оцениваем его
 CCardKit cCardKit_PlayerCopy;
 //добавляем в расклад игрока известные нам карты
 cCardKit_PlayerCopy.Copy(cCardKit_KnowPlayer);
 //доберём до шести карт (если получится, конечно)
 AddShopCard(cCardKit_PlayerCopy);
 //оценим расклад игрока
 int Status_Player=GetKitStatus(&cCardKit_PlayerCopy);
 //и решим, какой картой нам нужно ходить
 int StatusMoveCard=0;//статус карты, которой нужно ходить
 int d_status=1;//изменения статуса, если карта нужного статуса не будет найдена
 if (shop_card_status==0)//ожидается плохая карта из колоды
 {
  StatusMoveCard=0;
  d_status=-1;
 }
 if (shop_card_status==1)//ожидается средняя карта из колоды
 {
  d_status=-1;
  if (Status_My==0) StatusMoveCard=0;
  if (Status_My==1) StatusMoveCard=1;
  if (Status_My==2) StatusMoveCard=1;
 }
 if (shop_card_status==2)//ожидается хорошая карта из колоды
 {
  d_status=-1;
  if (Status_My==0) StatusMoveCard=0;
  if (Status_My==1) StatusMoveCard=1;
  if (Status_My==2)
  {
   if (Status_Player==0)
   {
    StatusMoveCard=2;
    d_status=1;
   }
   if (Status_Player==1)
   {
    StatusMoveCard=1;
    d_status=-1;
   }
   if (Status_Player==2)
   {
    StatusMoveCard=0;
    d_status=-1;
   }
  }
 }
 //а теперь выбираем карту с нужными характеристиками и минимальным значением
 int amount_my=cCardKit_PSP.GetAmount();
 while(done==false)
 {
  int min_price=100;
  int card_index=-1;
  //ищем карту
  for(n=0;n<amount_my;n++)
  {
   int price=GetPrice(cCardKit_PSP.GetCard(n));
   if (price<min_price)
   {
    min_price=price;
    card_index=n;
   }
  }
  if (card_index>=0) return(card_index);
  StatusMoveCard+=d_status;
  if (StatusMoveCard<0)
  {
   StatusMoveCard=1;
   d_status=1;
  }
  if (StatusMoveCard>2)
  {
   StatusMoveCard=1;
   d_status=-1;
  }
 }
 return(0);//сюда мы вообще не должны попасть
}
int  CGame::PSPOtherMove(void)
{
 int n,m;
 //определяем наш расклад до хода
 int Status_My=GetKitStatus(&cCardKit_PSP);//оцениваем наш расклад
 //теперь перебираем варианты, как мы можем походить
 int my_amount=cCardKit_PSP.GetAmount();
 for(n=0;n<my_amount;n++)
 {
  //берём карту
  SCard sCard_My=cCardKit_PSP.GetCard(n);
  //ищем такие карты на столе
  int player1_table_amount=cCardKit_TablePlayer1.GetAmount();
  int player2_table_amount=cCardKit_TablePlayer2.GetAmount();
  bool found=false;
  for(m=0;m<player1_table_amount;m++)
  {
   SCard sCardTable=cCardKit_TablePlayer1.GetCard(m);
   if (sCardTable.Value==sCard_My.Value)
   {
    found=true;
    break;
   }
  }
  for(m=0;m<player2_table_amount;m++)
  {
   SCard sCardTable=cCardKit_TablePlayer2.GetCard(m);
   if (sCardTable.Value==sCard_My.Value)
   {
    found=true;
    break;
   }
  }
  if (found==false) continue;
  //определяем, можем ли мы этой картой походить?
  //создаём набор без этой карты
  CCardKit cCardKit_PSPCopy;
  cCardKit_PSPCopy.Copy(cCardKit_PSP);
  cCardKit_PSPCopy.DeleteSCard(sCard_My);
  //добавляем в него произвольные карты из колоды
  AddShopCard(cCardKit_PSPCopy);
  //оцениваем набор
  int Status_MyMove=GetKitStatus(&cCardKit_PSPCopy);//оцениваем наш расклад
  //решаем, что делать
  if (Status_My==2) continue;//так ходить не будем
  if (Status_My==1)
  {
   if (Status_MyMove==0) continue;
  }
  if (Status_My==0)
  {
  }
  return(n);//делаем ход
 }
 return(GAME_OK);//бито
}
int CGame::PSPAnswer(void)
{
 int amount;
 SCard sCard;
 //допустим, мы берём карты
 CCardKit cCardKit_Get;//набор для взятых карт
 cCardKit_Get.Add(cCardKit_TablePlayer1);
 cCardKit_Get.Add(cCardKit_TablePlayer2);
 cCardKit_Get.Add(cCardKit_PSP);
 //оцениваем набор
 int Status_GetKit=GetKitStatus(&cCardKit_Get);
 //теперь смотрим, как мы можем ответить и как изменится оценка
 SCard sCardTable;
 sCardTable=cCardKit_TablePlayer1.PopCard();//берём последнюю карту со стола
 cCardKit_TablePlayer1.PushCard(sCardTable);//возвращаем её обратно
 amount=cCardKit_PSP.GetAmount();
 //выбираем наименьшую карту для хода
 int min_price=1000;
 int move_card=-1;//пока никакой не ходим
 for(int n=0;n<amount;n++)
 {
  sCard=cCardKit_PSP.GetCard(n);//берём карту
  if (CheckRule(sCardTable,sCard)==false) continue;//так ходить нельзя
  int price=GetPrice(sCard);
  if (price<=min_price)
  {
   min_price=price;
   move_card=n;
  }
 }
 if (move_card<0) return(GAME_GET);//нам нечем ходить
 //смотрим, как изменится оценка
 CCardKit cCardKit_PSPCopy;//карты компьютера
 cCardKit_PSPCopy.Add(cCardKit_PSP);
 sCard=cCardKit_PSP.GetCard(move_card);
 cCardKit_PSPCopy.DeleteSCard(sCard);
 //добавляем случайные карты из колоды
 if (AddShopCard(cCardKit_PSPCopy)==false) return(move_card);//если колода пустая - отбиваемся
 //оцениваем получившийся набор
 int Status_PSPCopyKit=GetKitStatus(&cCardKit_PSPCopy);
 //выбираем по таблице
 if (Status_GetKit==0)//расклад после взятия плохой
 {
  return(move_card);//будем бить
 }
 if (Status_GetKit==1)//расклад после взятия средний
 {
  if (Status_PSPCopyKit==0) return(GAME_GET);//возьмём
  if (Status_PSPCopyKit==1) return(move_card);//будем бить
  if (Status_PSPCopyKit==2) return(move_card);//будем бить
 }
 if (Status_GetKit==2)//расклад после взятия хороший
 {
  return(GAME_GET);//возьмём
 }
 return(GAME_GET);//возьмём
}
bool CGame::AddShopCard(CCardKit &cCardKit)
{
 //делаем копию колоды
 CCardKit cCardKit_ShopCopy;
 cCardKit_ShopCopy.Copy(cCardKit_Shop);//переносим туда карты колоды
 cCardKit_ShopCopy.Add(cCardKit_Player);//переносим туда карты игрока
 cCardKit_ShopCopy.Sub(cCardKit_KnowPlayer);//убираем оттуда карты игрока, которые мы знаем
 //смотрим, сколько в колоде вообще было карт
 int shop_amount=cCardKit_Shop.GetAmount();
 if (shop_amount==0) return(false);//колода пустая
 int cardkit_amount=cCardKit.GetAmount();
 while(cardkit_amount<6 && shop_amount>0)
 {
  //выбираем случайную карту
  int shop_copy_amount=cCardKit_ShopCopy.GetAmount();
  int card=RND(shop_copy_amount-1);
  cCardKit.PushCard(cCardKit_ShopCopy.GetCard(card));
  cCardKit_ShopCopy.DeleteCard(card);
  shop_amount--;
  cardkit_amount++;
 }
 return(true);
}
bool CGame::PlayerAddCard(char *Path)
{
 int n,m;
 SCard sCardTable;//карты на столе
 SCard sCard;
 //просим игрока подкинуть карты
 bool First=true;
 while(done==false)
 {
  //проверим, есть ли у игрока такие карты, какие и на столе
  bool end=true;
  int amount_player=cCardKit_Player.GetAmount();
  int amount_table_in=cCardKit_TablePlayer1.GetAmount();
  int amount_table_out=cCardKit_TablePlayer2.GetAmount();
  if (amount_table_in>=6) break;//больше нельзя подкидывать
  for(n=0;n<amount_player;n++)
  {
   sCard=cCardKit_Player.GetCard(n);
   for(m=0;m<amount_table_in;m++)
   {
    sCardTable=cCardKit_TablePlayer1.GetCard(m);
    if (sCardTable.Value==sCard.Value)
    {
     end=false;
     break;//такие карты уже есть на столе
    }
   }
   for(m=0;m<amount_table_out;m++)
   {
    sCardTable=cCardKit_TablePlayer2.GetCard(m);
    if (sCardTable.Value==sCard.Value)
    {
     end=false;
     break;//такие карты уже есть на столе
    }
   }
   if (end==false) break;
  }
  if (end==true) break;
  //если это начало блока, то выводим сообщение
  if (First==true) PutMessage(MESSAGE_GETADD);
  First=false;
  //попросим игрока добавить карты
  int card=GetPlayerCard(true,Path);
  if (card==GAME_RESTART) return(false);
  if (card==GAME_OK) break;//бито
  //проверим, что эти карты можно добавить
  sCard=cCardKit_Player.GetCard(card);
  //карты, которыми ходил игрок
  bool found=false;
  for(n=0;n<amount_table_in;n++)
  {
   sCardTable=cCardKit_TablePlayer1.GetCard(n);
   if (sCardTable.Value==sCard.Value)
   {
    found=true;
    break;//такие карты уже есть на столе
   }
  }
  //карты, которыми отбивались
  for(n=0;n<amount_table_out;n++)
  {
   sCardTable=cCardKit_TablePlayer2.GetCard(n);
   if (sCardTable.Value==sCard.Value)
   {
    found=true;
    break;//такие карты уже есть на столе
   }
  }
  if (found==false) continue;//так ходить нельзя
  //удаляем карту из известного нам набора карт игрока
  cCardKit_KnowPlayer.DeleteSCard(sCard);
  //кладём карту на стол
  cCardKit_Player.DeleteCard(card);
  cCardKit_TablePlayer1.PushCard(sCard);
 }
 if (First==true) PutMessage(MESSAGE_GET);
 //переносим карты компьютеру
 cCardKit_PSP.Add(cCardKit_TablePlayer1);
 cCardKit_PSP.Add(cCardKit_TablePlayer2);
 cCardKit_TablePlayer1.Clear();
 cCardKit_TablePlayer2.Clear();
 return(true);
}
void CGame::PSPAddCard(void)
{
 int n,m;
 while(done==false)
 {
  //проверим, что ещё можно подкидывать
  if (cCardKit_TablePlayer1.GetAmount()>=6) break;//уже добавлено 6 карт, больше нельзя
  bool FoundMove=false;
  //определяем наш расклад до хода
  int Status_My=GetKitStatus(&cCardKit_PSP);//оцениваем наш расклад
  //теперь перебираем варианты, как мы можем походить
  int my_amount=cCardKit_PSP.GetAmount();
  for(n=0;n<my_amount;n++)
  {
   //берём карты
   SCard sCard_My=cCardKit_PSP.GetCard(n);
   //ищем такие карты на столе
   int player1_table_amount=cCardKit_TablePlayer1.GetAmount();
   int player2_table_amount=cCardKit_TablePlayer2.GetAmount();
   bool found=false;
   for(m=0;m<player1_table_amount;m++)
   {
    SCard sCardTable=cCardKit_TablePlayer1.GetCard(m);
    if (sCardTable.Value==sCard_My.Value)
    {
     found=true;
     break;
    }
   }
   for(m=0;m<player2_table_amount;m++)
   {
    SCard sCardTable=cCardKit_TablePlayer2.GetCard(m);
    if (sCardTable.Value==sCard_My.Value)
    {
     found=true;
     break;
    }
   }
   if (found==false) continue;
   //определяем, можем ли мы этой картой походить?
   //создаём набор без этой карты
   CCardKit cCardKit_PSPCopy;
   cCardKit_PSPCopy.Copy(cCardKit_PSP);
   cCardKit_PSPCopy.DeleteSCard(sCard_My);
   //добавляем в него произвольные карты из колоды
   AddShopCard(cCardKit_PSPCopy);
   //оцениваем набор
   int Status_MyMove=GetKitStatus(&cCardKit_PSPCopy);//оцениваем наш расклад
   //решаем, что делать
   if (Status_My==2) continue;//так ходить не будем
   if (Status_My==1)
   {
    if (Status_MyMove==0) continue;
   }
   if (Status_My==0)
   {
   }
   //переносим карту на стол
   cCardKit_TablePlayer1.PushCard(sCard_My);
   cCardKit_PSP.DeleteCard(n);//удаляем карту
   FoundMove=true;
   break;
  }
  if (FoundMove==false) break;//больше ходить нечем
 }
 //переносим все карты игроку
 cCardKit_Player.Add(cCardKit_TablePlayer1);
 cCardKit_KnowPlayer.Add(cCardKit_TablePlayer1);
 cCardKit_Player.Add(cCardKit_TablePlayer2);
 cCardKit_KnowPlayer.Add(cCardKit_TablePlayer2);
 cCardKit_TablePlayer1.Clear();
 cCardKit_TablePlayer2.Clear();
}
int CGame::MoveProcessing(bool PSPMove,char *Path)
{
 SCard sCard;//просто карта
 SCard sCardTable;//карта на столе
 int ReturnMove=MOVE_PSP;//возвращаемое значение того, кто будет ходить
 int next_player=MOVE_PLAYER;//новое значение того, кто ходит
 int n;
 CCardKit *cCardKit_Player1=&cCardKit_PSP;//игрок, который ходит
 CCardKit *cCardKit_Player2=&cCardKit_Player;//игрок, который отбивается
 if (PSPMove==false)
 {
  next_player=MOVE_PSP;
  ReturnMove=MOVE_PLAYER;
  cCardKit_Player1=&cCardKit_Player;
  cCardKit_Player2=&cCardKit_PSP;
 }
 while(done==false)
 {
  //проверим, что у игрока 1 есть карты
  if (cCardKit_Player1->GetAmount()==0)
  {
   if (PSPMove==true) PutMessage(MESSAGE_OK);
   ReturnMove=next_player;
   break;
  }
  //проверим, что у игрока 2 есть карты
  if (cCardKit_Player2->GetAmount()==0)
  {
   if (PSPMove==true) PutMessage(MESSAGE_OK);
   ReturnMove=next_player;
   break;
  }
  //проверим, что игрок ходил не более шести раз
  if (cCardKit_TablePlayer2.GetAmount()>=6)
  {
   if (PSPMove==true) PutMessage(MESSAGE_OK);
   ReturnMove=next_player;
   break;
  }
  //получаем, как ходит игрок 1
  int player1_card;
  if (PSPMove==true) player1_card=GetPSPCard(true);
                else player1_card=GetPlayerCard(true,Path);
  //смотрим, сколько карт на игровом поле
  int amount_table_in=cCardKit_TablePlayer1.GetAmount();
  int amount_table_out=cCardKit_TablePlayer2.GetAmount();
  if (player1_card==GAME_RESTART) return(MOVE_RESTART);
  if (player1_card==GAME_OK)//бито
  {
   if (PSPMove==true) PutMessage(MESSAGE_OK);
   if (amount_table_in==0) continue;//игрок ещё не ходил
   ReturnMove=next_player;
   break;//передаём ход
  }
  sCard=cCardKit_Player1->GetCard(player1_card);
  //игрок волен ходить, как угодно первой картой
  if (amount_table_in!=0)//игрок уже ходил
  {
   bool Found=false;
   //карты, которыми ходил игрок
   for(n=0;n<amount_table_in;n++)
   {
    sCardTable=cCardKit_TablePlayer1.GetCard(n);
    if (sCardTable.Value==sCard.Value)
    {
     Found=true;
     break;//такие карты уже есть на столе
    }
   }
   //карты, которыми отбивались
   for(n=0;n<amount_table_out;n++)
   {
    sCardTable=cCardKit_TablePlayer2.GetCard(n);
    if (sCardTable.Value==sCard.Value)
    {
     Found=true;
     break;//такие карты уже есть на столе
    }
   }
   if (Found==false) continue;//неверный ход
  }
  //удаляем карту из известного нам набора карт игрока
  if (PSPMove==false) cCardKit_KnowPlayer.DeleteSCard(sCard);//раз ходил игрок
  //перемещаем выбранную карту на поле
  cCardKit_Player1->DeleteCard(player1_card);
  cCardKit_TablePlayer1.PushCard(sCard);
  Video_ClearScreen();
  //рисуем карты
  PutKit(false);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  //теперь отвечает игрок 2
  int player2_card=0;
  while(done==false)
  {
   if (PSPMove==true) player2_card=GetPlayerCard(false,Path);
                 else player2_card=GetPSPCard(false);
   if (player2_card==GAME_RESTART) return(MOVE_RESTART);
   if (player2_card==GAME_GET)//игрок 2 берёт
   {
    //добавляем карты, если хотим
    if (PSPMove==true) PSPAddCard();//добавляет компьютер
    else//добавляет человек
    {
     if (PlayerAddCard(Path)==false) return(MOVE_RESTART);
    }
    //ход всё ещё у игрока 1
    break;
   }
   //проверим, что ход корректный
   sCard=cCardKit_Player2->GetCard(player2_card);//карта, которой ответил игрок 2
   sCardTable=cCardKit_TablePlayer1.PopCard();//берём последнюю карту со стола
   cCardKit_TablePlayer1.PushCard(sCardTable);//возвращаем её обратно
   if (CheckRule(sCardTable,sCard)==true) break;//ход по правилам
  }
  if (player2_card==GAME_GET) break;//игрок 2 берёт
  if (PSPMove==true) cCardKit_KnowPlayer.DeleteSCard(sCard);//раз ходил игрок
  //переносим карту на поле
  cCardKit_Player2->DeleteCard(player2_card);
  cCardKit_TablePlayer2.PushCard(sCard);
  //отрисовываем поле
  Video_ClearScreen();
  //рисуем карты
  PutKit(false);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
 }
 //отрисовываем поле
 Video_ClearScreen();
 //рисуем карты
 PutKit(false);
 Video_ViewDisplayPage();
 Video_ChangeDisplayPage();
 //оцениваем состояние игры
 int end=CheckEndGame();
 if (end==END_PSP) PutMessage(MESSAGE_PSP_WIN);
 if (end==END_PLAYER) PutMessage(MESSAGE_PLAYER_WIN);
 if (end==END_PARITAT) PutMessage(MESSAGE_PARITAT);
 if (end!=END_NO) return(MOVE_WAIT);
 //переносим карты со стола в "бито"
 cCardKit_TablePlayer1.Clear();
 cCardKit_TablePlayer2.Clear();
 //добираем карты из колоды до шести
 int amount=cCardKit_Player1->GetAmount();
 for(n=amount;n<6;n++)
 {
  sCard=cCardKit_Shop.PopCard();
  if (sCard.Value==0) break;//колода закончилась
  cCardKit_Player1->PushCard(sCard);
 }
 amount=cCardKit_Player2->GetAmount();
 for(n=amount;n<6;n++)
 {
  sCard=cCardKit_Shop.PopCard();
  if (sCard.Value==0) break;//колода закончилась
  cCardKit_Player2->PushCard(sCard);
 }
 return(ReturnMove);
}
bool CGame::CheckRule(SCard sCardTable,SCard sCard)
{
 //проверяем правила игры
 if (sCard_Main.Suit!=sCard.Suit)//если отбивались не козырем
 {
  if (sCardTable.Suit!=sCard.Suit) return(false);//нарушены правила
  if (sCard.Value<=sCardTable.Value) return(false);//нарушены правила
 }
 if (sCard_Main.Suit==sCard.Suit && sCardTable.Suit==sCard_Main.Suit)//если отбивались козырем и отбивали козырь
 {
  if (sCard.Value<=sCardTable.Value) return(false);//нарушены правила
 }
 return(true);
}
int CGame::GetPrice(SCard sCard)
{
 int price=sCard.Value-5;
 if (sCard.Suit==sCard_Main.Suit) price+=10;
 return(price);
}
int CGame::GetStatusCard(SCard sCard)
{
 int price=GetPrice(sCard);
 if (price<=5) return(0);//плохая карта
 if (price>=10) return(2);//хорошая карта
 return(1);//средняя карта
}
int CGame::CheckEndGame(void)
{
 if (cCardKit_Shop.GetAmount()!=0) return(END_NO);//игра продолжается
 int psp=cCardKit_PSP.GetAmount();
 int player=cCardKit_Player.GetAmount();
 if (psp==0 && player==0) return(END_PARITAT);//ничья
 if (psp==0) return(END_PSP);//выиграл компьютер
 if (player==0) return(END_PLAYER);//выиграл игрок
 return(END_NO);//игра продолжается
}
int CGame::GetKitStatus(CCardKit *cCardKit)
{
 int n;
 int amount=cCardKit->GetAmount();
 float middle_value=0;
 for(n=0;n<amount;n++)
 {
  SCard sCard=cCardKit->GetCard(n);
  int price=GetPrice(sCard);
  middle_value+=price;
 }
 if (amount==0) return(1);
 middle_value/=(float)amount;
 if (middle_value<=4.83) return(0);//плохой расклад
 if (middle_value>=12.085) return(2);//хороший расклад
 return(1);//средний расклад
}
void CGame::PutMessage(int message)
{
 SceCtrlData pad;
 //выводим графику
 Video_ClearScreen();
 if (Move==MOVE_WAIT) PutKit(true);
                 else PutKit(false);
 //выводим картинку
 if (message==MESSAGE_OK) cSprite_MessageOk.Put(176,104,false);
 if (message==MESSAGE_GET) cSprite_MessageGet.Put(176,104,false);
 if (message==MESSAGE_GETADD) cSprite_MessageGetAdd.Put(176,104,false);
 if (message==MESSAGE_PSP_WIN) cSprite_MessageWinPSP.Put(176,104,false);
 if (message==MESSAGE_PLAYER_WIN) cSprite_MessageWinPlayer.Put(176,104,false);
 if (message==MESSAGE_PARITAT) cSprite_MessageParitat.Put(176,104,false);
 Video_ViewDisplayPage();
 Video_ChangeDisplayPage();
 while(done==false)
 {
  sceCtrlReadBufferPositive(&pad,1);//считываем клавиши
  if (!(pad.Buttons&PSP_CTRL_CROSS)) break;
 }
 while(done==false)
 {
  sceCtrlReadBufferPositive(&pad,1);//считываем клавиши
  if (pad.Buttons&PSP_CTRL_CROSS) break;
 }
}
int CGame::SelectMove(void)
{
 int n;
 //ищем минимальный козырь у игрока и у компьютера
 SCard sCard_PSP;
 SCard sCard_Player;

 sCard_PSP.Suit=0;
 sCard_PSP.Value=0;
 sCard_Player.Suit=0;
 sCard_Player.Value=0;

 int amount=cCardKit_Player.GetAmount();
 for(n=0;n<amount;n++)
 {
  SCard sCard=cCardKit_Player.GetCard(n);
  if (sCard.Suit==sCard_Main.Suit)
  {
   if (sCard_Player.Value==0)
   {
    sCard_Player.Suit=sCard.Suit;
    sCard_Player.Value=sCard.Value;
   }
   if (sCard_Player.Value>sCard.Value)
   {
    sCard_Player.Suit=sCard.Suit;
    sCard_Player.Value=sCard.Value;
   }
  }
 }
 amount=cCardKit_PSP.GetAmount();
 for(n=0;n<amount;n++)
 {
  SCard sCard=cCardKit_PSP.GetCard(n);
  if (sCard.Suit==sCard_Main.Suit)
  {
   if (sCard_PSP.Value==0)
   {
    sCard_PSP.Suit=sCard.Suit;
    sCard_PSP.Value=sCard.Value;
   }
   if (sCard_PSP.Value>sCard.Value)
   {
    sCard_PSP.Suit=sCard.Suit;
    sCard_PSP.Value=sCard.Value;
   }
  }
 }
 if (sCard_PSP.Value!=0)
 {
  if (sCard_Player.Value==0) return(MOVE_PSP);
  if (sCard_Player.Value<sCard_PSP.Value) return(MOVE_PLAYER);
  return(MOVE_PSP);
 }
 if (sCard_Player.Value!=0)
 {
  if (sCard_PSP.Value==0) return(MOVE_PLAYER);
  if (sCard_Player.Value>sCard_PSP.Value) return(MOVE_PSP);
  return(MOVE_PLAYER);
 }
 //нет козырей ни у кого - выбираем случайным образом
 if (RND(100)>=50) return(MOVE_PSP);
 return(MOVE_PLAYER);
}

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <pspdisplay.h>
#include <string.h>
//----------------------------------------------------------------------------------------
#include "cgame.h"
#include "video.h"
//----------------------------------------------------------------------------------------
PSP_MODULE_INFO("Fool", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER|THREAD_ATTR_VFPU);

void dump_threadstatus(void);

bool done=false;

int exit_callback(int arg1,int arg2,void *common)
{
 done=true;
 return(0);
}
int CallbackThread(SceSize args, void *argp)
{
 int cbid;
 cbid=sceKernelCreateCallback("Exit Callback",exit_callback,NULL);
 sceKernelRegisterExitCallback(cbid);
 sceKernelSleepThreadCB();
 return(0);
}
int SetupCallbacks(void)
{
 int thid = 0;
 thid=sceKernelCreateThread("update_thread",CallbackThread,0x11,0xFA0,0,0);
 if(thid>=0) sceKernelStartThread(thid, 0, 0);
 return(thid);
}
//----------------------------------------------------------------------------------------
//начинаем программу
int main(int argc, char  **argv)
{
 int n;
 int argv_len=strlen(argv[0]);
 //формируем имя файла уровня
 //отматываем до черты
 for(n=argv_len;n>0;n--)
 {
  if (argv[0][n-1]=='/')
  {
   argv[0][n]=0;//обрубаем строку
   break;
  }
 }
 //устанавливаем обработчики
 SetupCallbacks();
 //инициализируем графический режим
 Video_InitDisplay();
 Video_SetDisplayPage(0);
 //настраиваем управление
 sceCtrlSetSamplingCycle(0);
 sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
 //запускаем игру
 CGame cGame;
 cGame.Create(argv[0]);
 cGame.Activate(argv[0]);
 //выходим из программы
 sceKernelExitGame();
 return(0);
}


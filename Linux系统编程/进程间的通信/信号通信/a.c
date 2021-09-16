//信号通信
//信号在内核中已经存在，各种信号函数运用；
//kill -l查看信号
//告诉信号类型，发送目标
    //int kill（pid，sig），进程id，类型
    
    //raise（类型）；信号发给自己，当前进程；
    //alarm（n），等待一段时间发送闹钟信号，只发给当前进程，终止进程。
    //ctrl+c也是一种信号，键盘驱动发送
    //pause（）一直进入S睡眠态
    
    //signal(signum,function);自己处理某个信号，有signum决定。 
   
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "stdlib.h"
#include "signal.h"
void myfunction(int signum){
     int i=0;
     while(i<5){
     printf("myfunction resolve signum=%d\n",signum);
     i++;
    }
}
int main(){
  int i=0;
  signal(14,myfunction);
  alarm(8);//触发myfunction
  //signal(14,SIG_IGN);表示忽视，最新的处理会掩盖之前的signal
  //signal(14,SIG_DFL);//默认处理
  while(i<15){
   printf("main %d\n",i);
   sleep(1);
   i++;
  }
}


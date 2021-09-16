//AB进程共享内存结合信号读写,A写B读
//各自将pid写入内核内存，便于对方获取,kill(pid,sig)才有效;
//为了分别存pid和数据，定义一个结构体，将结构体指针取代char *p,
//相当于将原来只能存数据的内存拓展为可以存pid和数据。
//struct mystruct{
//  int abpid；
//  char buf[124];
// }

//结构体指针struct mystruct *p；

//IPC_PRIVAT创key=ftok("ftok.c",'a');
//shmget(key,128,PIC_CREAT|0777);
	

#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "stdlib.h"
#include "signal.h"
#include "sys/shm.h"
	
void myfun(int signum){
  return;
}

struct mystruct{
int abpid;
char buf[124];
 };

struct mystruct *p;
int main(){
int shmid;
int key;
key=ftok("ftokfile.c",'a');
int pid;//注意在函数内，pid最初为0，AB是一样的，这就是为什么，
        //第一次就能由pid找到对方

 shmid=shmget(key,128,IPC_CREAT|0777);
 if(shmid<0){
     printf("creat shared mem failure\n");
     return -1;
   }
     printf("creat shared mem sucess\n");
     printf("shmid=%d\n",shmid);
     printf("key=%x\n",key);


     p=(struct mystruct *)shmat(shmid,NULL,0);
     while(1){
        signal(6,myfun);
        printf("A process write:\n");
        fgets(p->buf,128,stdin);
        printf("write sucess\n");
        pid=p->abpid;//获取共享区域的pid，就是对方的
        p->abpid=getpid();//将当前pid传入，以便下一次对方获取
        kill(pid,5);//获取了对方的pid，所以这里目标是对方，信号类型5
        pause();//睡眠，等待下一次被唤醒

        }

        return 0;
}

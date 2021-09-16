#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/shm.h"
#include "stdlib.h"
#include "signal.h"
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
 int pid;

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
        signal(5,myfun);//5与对面一样
        pid=p->abpid;
        p->abpid=getpid();
        printf("shm shared mem is:%s",p->buf);
        kill(pid,6);
        pause();

        }

        return 0;
}


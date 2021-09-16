
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "stdlib.h"
#include "signal.h"
#include "sys/shm.h"

struct msgbuf{
long type;
char buf[124];
 };
int main(){
 int msgid;
 int key;
 key=ftok("ftokfile.c",'a');
 int pid;
struct msgbuf  msgbuf1,msgbuf2;
 msgid=msgget(key,IPC_CREAT|0777);
 if(msgid<0){
         printf("creat msg failure\n");
         return -1;
       }
         printf("creat msg sucess\n");
         printf("msgid=%d\n",msgid);
   pid=fork();
   if(pid==0){
                msgbuf1.type=100;
                while(1){
                printf("B msg  process write:\n");
                memset(msgbuf1.buf,0,124);
   fgets(msgbuf1.buf,124,stdin);
                printf("write sucess\n");
                msgsnd(msgid,(void *)&msgbuf1,strlen(msgbuf1.buf),0);
                 }
        }

  if(pid>0){
                while(1){
                memset(msgbuf2.buf,0,124);
                msgrcv(msgid,(void *)&msgbuf2,124,200,0);
                printf("B read sucess:%s\n",msgbuf2.buf);
                 }
        }
        return 0;
}

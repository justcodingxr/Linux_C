//消息队列（链式队列）
//msgget:key,IPC_PRIVATE（key始终是0）
//   权限
//  返回msgid

//msgsnd(msgid，*msgbuff1，size，flag）;写，插入
   
// *msgp写的内容，下列形式
// struct msgbuf{
//   long type;
//   char buf[N];
//   ...
//  }
	
//0阻塞方式
//例如：msgsnd(msgid，（void *)&msgbuf，strlen(msgbuf.buf),0）;
//	msgdt（msgid）：
//	msgrcv读：删除，可以设置阻塞，不需要信号。
//	msgrcv（msgid,*msgbuf2,size,type，0);
	
//	msgctl(msgid,cmd,struct)对消息队列操作
//      cmd:1.IPC_STAT,获取对象属性  struct  实现ipcs -q
//          2.IPC_SET  设置属性      struct  修改属性
//          3.IPC_RMID 删除对象      NULL    实现ipcrm -q
//          system("ipcs -q\n");
//          msgctl(msgid,IPC_RMID,NULL);
//          system("ipcs -q\n");

//      ipcs看共享内存ipcs -m
//      ipcrm -m shmid删除

//      A父子进程写读，B父子进程读写；读写类型也相反。
//      其他代码一样，A,B对读写struct一样使用。

#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/msg.h"
#include "stdlib.h"
#include "signal.h"
#include "stdio.h"
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
   if(pid>0){
        msgbuf1.type=200;
        while(1){
           printf("A msg  process write:\n");
           memset(msgbuf1.buf,0,124);
           fgets(msgbuf1.buf,124,stdin);
           printf("write sucess\n");
           msgsnd(msgid,(void *)&msgbuf1,strlen(msgbuf1.buf),0);
           }
        }
  if(pid==0){
           while(1){
           memset(msgbuf2.buf,0,124);
           msgrcv(msgid,(void *)&msgbuf2,124,100,0);//msgrcv读操作
           printf("A read sucess:%s\n",msgbuf2.buf);
           }
        }
   return 0;
}

//父子进程共享内存结合信号读写
//1.先创建共享内存后fork，shmid复制，这样父子对同一内存操作
//2.父进程映射shmat，便以从用户空间键盘输入
//3.父进程写，写完后，给子进程信号，进入睡眠pause（）；
//  等待子进程信号唤醒，继续写
//4.子进程一进入while，pause（）等待父进程信号唤醒，读，读完回到while的pause（）
//5.对于随意给定的信号值，为避免不想的操作，在处理函数之前自定义处理函数，
// 再回到处理函数进行下面
//6.pid子进程，getppid（）父进程，p=（char *）shmat(shmid,NULL,0);
// 父子都对同一内核内存操作，映射到各自的进程对象不同，不同的p


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
int main(){
 int shmid;
 int key;
 pid_t pid;
 char *p;

 //创建共享内存
 shmid=shmget(IPC_PRIVATE,128,0777);
 if(shmid<0){
         printf("creat shared mem failure\n");
         return -1;
       }
         printf("creat shared mem sucess\n");
         printf("shmid=%d\n",shmid);
         printf("key=%x\n",key);
   pid=fork();//父
   if(pid>0){
        p=(char *)shmat(shmid,NULL,0);
        while(1){
        signal(6,myfun);
        printf("parent write:\n");
        fgets(p,128,stdin);
        printf("write sucess\n");
        kill(pid,5);//对目标对象pid发送信号，信号类型5，触发signal（6，myfun）
        pause();//睡眠直到被唤醒

        }
      }
   if(pid==0){
       p=(char *)shmat(shmid,NULL,0);
      while(1){
       signal(5,myfun);
       pause();
       printf("son read shared mem:%s\n",p);
       kill(getppid(),6);//对父，getpid发送信号，信号类型6，
                          //触发signal（6，myfun）,而不是signal（5，myfun）
      }

   }

    return 0;
 }


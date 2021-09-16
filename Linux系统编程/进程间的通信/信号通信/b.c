#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "stdlib.h"
#include "signal.h"
void fun1(int signum){
        printf("signal1 resolve %d\n",signum);
        printf("signal1 resolve %d\n",signum);
         printf("signal1 resolve %d\n",signum);
        printf("signal1 resolve %d\n",signum);
        return;
}
void fun2(int signum){
        printf("receive sonpid\n");
        printf("signal2 exit pid %d\n",signum);
        printf("signal2 exit pid %d\n",signum);
        printf("signal2 exit pid %d\n",signum);


        wait(NULL);
        return;
}


int main(){
 pid_t pid;
 int i;
 i=0;
 pid=fork();
 //父进程
 if(pid>0){
         signal(10,fun1);
         signal(17,fun2);
 while(1){
         printf("parent process %d\n",i);
         sleep(1);
         i++;
    }

 }
//子进程
 if(pid==0){
 sleep(7);
 kill(getppid(),10);//触发父进程的signal
 exit(0);//17，触发父进程的signal

 }
return 0;
           
}

//多线程编程
//fork进程创建会复制资源，线程确是在进程中共享资源。
//多线程共享进程内存，指的是mm-struct所指的进程虚拟地址空间，习惯上叫内存；
//进程共享0-3G用户空间，3-4G内核空间，内核单份拷贝，
//用户空间多份拷贝;用户空间3G地址划分为多个虚拟内存区域进行管理VMA，又叫段，数据//段、代码段，内存映射文件mmp是有名映射，共享内存映射无名
	//mmp建立的VMA等；lib库的多个数据段、代码段、bss段等。
	//进程的虚拟内存分布在/proc/pid /maps查看；
	
    //并发:单核，假象
    //并行：多核
    //同步：防止同时发生
    //异步：独立发生
	
//pthread不是linux下的默认的库，也就是在链接的时候，
//无法找到phread库中哥函数的入口地址，于是链接会失败。
//-lpthread是老版本的gcc编译器用的，
//在新版本中应该用-pthread取代-lpthread



#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/msg.h"
#include "stdlib.h"
#include "signal.h"
#include "stdio.h"
#include "sys/shm.h"

void *thread_fun1(void *argv){
   if(strcmp("1",(char *)argv)==0){
   printf("thread_fun1 return\n");
   return (void *) 1;
    }

   if(strcmp("2",(char *)argv)==0){
   printf("thread_fun1 pthread_exit\n");
   pthread_exit((void *) 1);

   }
   if(strcmp("3",(char *)argv)==0){
   printf("thread_fun1 exit\n");
   exit(3);//会终止进程导致主线程退出
   }

}


int main(int argc,char *argv[]){
   int ret;
   pthread_t tid;
   ret=pthread_create(&tid,NULL,thread_fun1,(void *)argv[1]);
   if(ret!=0){
         printf("creat thread failure\n");
         return 0;
    }
   sleep(1);//保证主线程执行
   printf("main thread end\n");
   return 0;
}

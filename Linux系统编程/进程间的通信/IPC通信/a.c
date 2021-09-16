//IPC通信
//共享内存：创建后在内存中，可多次读
//shmget(key,大小，IPC_PRIVATE |权限）
//key,ftok获得大小,权限
//创建共享内存  
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "stdlib.h"
#include "signal.h"

#include "sys/shm.h"
int main(){
 int shmid;
 int key;
 char *p=NULL;
 key=ftok("ftokfile.c",'b');
 shmid=shmget(key,128,IPC_CREAT|0777);
 if(shmid<0){
    printf("creat shared mem failure\n");       
    return -1;
   }
    printf("creat shared mem sucess\n");
    printf("shmid=%d\n",shmid);
    printf("key=%x\n",key);

//（void *） shmat（shmid，NULL,0）；
//将共享内存映射到用户空间
//NULL表示自动映射，0表示可读写，返回值未 void指针
     
 p=(char *)shmat(shmid,NULL,0);
 if(p==NULL){
  printf("shmat failure\n");
  return -1;
 }
  printf("shmat sucess\n");
  printf("putin: \n");
  fgets(p,128,stdin);
  printf("shared mem is:%s",p);

  shmdt(p);
  shmctl(shmid,IPC_RMID ,NULL);//对内核共享内存操作
  return 0;

}

//shmdt（shmat返回值）：将用户空间地址映射删除，缓存还在
//shmctl(shmid,cmd,struct)//对内核共享内存操作
// cmd:1.IPC_STAT,获取对象属性  struct  实现ipcs -m
//     2.IPC_SET  设置属性      struct  
//     3.IPC_RMID 删除对象       NULL  实现ipcrm -m
//     system("ipcs -m\n");
//     shmctl(shmid,IPC_RMID,NULL);
//     system("ipcs -m\n");

//    ipcs看共享内存ipcs -m
//    ipcrm -m shmid删除

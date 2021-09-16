//进程间通信，基于文件io
//进程A,B在用户空间无法进行，进入内核才行；
//线程可以在用户空间通信；
	
//单机模式通信（一个Linux核）
//1.管道通信
//管道读完了内容就删了，无可读会阻塞，写满会阻塞
//无名管道：只能进行父子进程
// int pipe(int fd[2]);成功返回0，失败返回-1，参数fd中存文件描述符
// 相当于fd，fd[1]用于写，fd[0]用于读
	//有名管道：两个进程之间
	//mkfifo（name,mode)创建管道文件，权限umask有关	
	//有名管道文件，字符设备，块设备，套接字只有文件节点，不占磁盘空间。
	//open打开管道文件时，就在内核创建了管道
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "stdlib.h"
int main(){
    int fd;
    int i;
    char process_i=0;
    fd=open("fifo",O_WRONLY);
    if(fd<0){
	printf("open fifo failure\n");
    return -1;
    }
    printf("open fifo sucess\n");

        for( i=0;i<5;i++){
        printf("A process %d\n",i);
    }
        process_i=1;
        sleep(7);
        write(fd,&process_i,1);
    while(1);
    return 0;

}

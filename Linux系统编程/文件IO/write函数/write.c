//write函数，writebuf[]="agdhjwd"写入a.c，
//将writebuf中数据写入a.c，lseek定位到头部，
//读128字节到readbuf并打印

#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
int main(int argc ,char *argv[])
    {
      int fd,wl,rl;
      fd=open("a.c",O_TRUNC | O_RDWR,0777);
      char writebuf[]="agdhjwd";
      char readbuf[128]={0};
      if(fd<0)
      {
          printf("open file a.c failure\n");
          return -1;
        }
     printf("open file a.c successfully\n");
        
     wl= write(fd,writebuf,sizeof(writebuf));
     printf("write sucessfully %d\n",wl);
        
     lseek(fd,0,SEEK_SET);//fd定位到首部
     //lseek(fd,-3,SEEK_CUR);当前
     //lseek(fd,-3,SEEK_END);尾部
        
     rl=read(fd,readbuf,128);//读到readbuf
     printf("read successfully  %d  %s\n",rl,readbuf);
     close(fd);
     return 0;
}


//文件IO，直接调用内核提供的系统调用，站在应用层：
//open权限和umask码有关
//umask 设置掩码
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
int main(int argc ,char *argv[])
{
    int fd;
    fd=open("appendata.c",O_APPEND | O_RDWR,0777);
        if(fd<0)
        {
            printf("open file appenddata failure\n");
            return -1;
        }
        printf("open file appendata successfully\n");
        close(fd);
        return 0;

}


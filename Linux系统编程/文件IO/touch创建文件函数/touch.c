//touch函数
//O_CREAT | O_EXCL创建已经存在的文件返回-1
//O_CREAT重新创建
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
int main(int argc ,char *argv[])
{
    int fd;
    fd=open(argv[1],O_CREAT | O_RDWR,0777);
        if(fd<0)
        {
            printf("create file %s failure\n",argv[1]);
            return -1;
        }
        printf("create file %s successfully\n",argv[1]);
        close(fd);
        return 0;
}

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
    fd=open("fifo",O_RDONLY);
    if(fd<0){
            printf("open fifo failue\n");
            return -1;
        }
        
     printf("open fifo sucess\n");
     read(fd,&process_i,1);
     while(process_i==0);

     for( i=0;i<5;i++){
     printf("B process %d\n",i);

    }
    while(1);
    return 0;

}

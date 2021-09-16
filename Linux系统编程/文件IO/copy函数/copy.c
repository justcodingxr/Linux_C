//copy a.c b.c
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
int main(int argc,char *argv[]){
	int rfd,wfd;
	int rl,wl;
	if(argc < 3){
	printf("error!");
	return -3;
	}
	
	rfd=open(argv[1],O_RDONLY);
	wfd=open(argv[2],O_WRONLY);

	if(rfd < 0){
        printf("open readfile %s failure",argv[1]);
	return -1;
	}

	if(wfd < 0){
	printf("open writefile %s failure",argv[2]);
	return -2;
	}  
	
	char buf[128];
	
	while(1){
	
	rl=read(rfd,buf,128);
	
	if(rl<128)
    break;

	wl=write(wfd,buf,rl);
	}
	
	
	write(wfd,buf,rl);
	printf("copy successful");
	//rfd到后面，最后不到128字节再写一遍
	return 0;

}

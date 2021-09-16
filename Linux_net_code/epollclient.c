#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#define SERV_PORT 8000
#define SERV_IP "127.168.156.1"
int main(){
        int cfd;
        cfd=socket(AF_INET,SOCK_STREAM,0);
	
        struct sockaddr_in saddr;
  	saddr.sin_family=AF_INET;
        saddr.sin_port=htons(SERV_PORT);
        saddr.sin_addr.s_addr=htonl(INADDR_ANY);

        socklen_t saddrlen;
        saddrlen=sizeof(saddr);
        
	connect(cfd,(struct sockaddr*)&saddr,sizeof(saddr));

        char buf[128]={0};
        int n;
        while(1){
		fgets(buf,sizeof(buf),stdin);
               
                write(cfd,buf,strlen(buf));
		n=read(cfd,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,n);
	   }
	close(cfd);
}


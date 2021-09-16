#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#define SERV_PORT 7000
int main(int argc,char *argv[]){
	int sfd,n;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
       char buf[BUFSIZ];	
	struct sockaddr_in saddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(SERV_PORT);
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);


	while(fgets(buf,BUFSIZ,stdin)!=NULL){
		n=sendto(sfd,buf,strlen(buf),0,(struct sockaddr *)&saddr,sizeof(saddr));
		
		for(int i=0;i<n;i++){
			buf[i]=toupper(buf[i]);
		}
		n=recvfrom(sfd,buf,n,0,NULL,0);
		write(STDOUT_FILENO,buf,n);
	}
	close(sfd);
}

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#define SERV_PORT 7000
int main(void){
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in saddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(SERV_PORT);
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);


bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	caddrlen=sizeof(caddr);
	char buf[BUFSIZ];
	int n;
	while(1){
		n=recvfrom(sfd,buf,BUFSIZ,0,(struct sockaddr *)&caddr,&caddrlen);
		
		for(int i=0;i<n;i++){
			buf[i]=toupper(buf[i]);
		}
		n=sendto(sfd,buf,n,0,(struct sockaddr *)&caddr,sizeof(caddr));
		
	}
	close(sfd);
	return 0;
}

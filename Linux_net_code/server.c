#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>
#define SERV_PORT 6666
#define SERV_IP "127.168.156.1"
int main(){
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(SERV_PORT);
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);


	bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));

	listen(sfd,128);

	int cfd;
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	caddrlen=sizeof(caddr);
	cfd=accept(sfd,(struct sockaddr *)&caddr,&caddrlen);

	char buf[128]={0};
	int n;
	while(1){
		n=read(cfd,buf,sizeof(buf));
		for(int i=0;i<n;i++){
			buf[i]=toupper(buf[i]);
		}
		write(cfd,buf,n);
	}
	close(sfd);
	close(cfd);

}

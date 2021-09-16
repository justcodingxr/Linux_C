#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>
#define SERV_PORT 8000
#define MAXLINE 8192
#define OPEN_MAX 5000


void perr_exit(const char *s)
{
    perror(s);
    exit(-1);
}
 
int main(int argc,char *argv[])
{	int i,connfd,sockfd;
	int listenfd;
	int n=0,num=0;
	ssize_t nready,efd,res;
	char buf[MAXLINE],str[INET_ADDRSTRLEN];
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	socklen_t clilen;
	struct sockaddr_in saddr,caddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(SERV_PORT);
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	struct epoll_event tep,ep[OPEN_MAX];

	bind(listenfd,(struct sockaddr *)&saddr,sizeof(saddr));

	listen(listenfd,20);
	efd=epoll_create(OPEN_MAX);
	if(efd==-1){
	  perr_exit("epoll_create error");
	}
	tep.events=EPOLLIN;tep.data.fd=listenfd;
	res=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);
	if(res==-1)
		perr_exit("epoll_ctl error");

	

	for(; ;){
		nready=epoll_wait(efd,ep,128,-1);
		if(nready==-1)
			perr_exit("epoll_wait erro");
		for(int i=0;i<nready;i++){
			if(!(ep[i].events&EPOLLIN))
				continue;
		
			if(ep[i].data.fd==listenfd){
   		        clilen=sizeof(caddr);
		        connfd=accept(listenfd,(struct sockaddr*)&caddr,&clilen);
			tep.events=EPOLLIN;tep.data.fd=connfd;
			res=epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);
			if(res==-1)
			perr_exit("epoll_ctl erro");
			}else{
				sockfd=ep[i].data.fd;	
				n=read(sockfd,buf,MAXLINE);
				if(n==0){
				res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
				if(res==-1)
				perr_exit("epoll_ctl error");
				close(sockfd);
				}else if(n<0){
				perror("read error");
				res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
				close(sockfd);
				}else{
					for(i=0;i<n;i++){
					buf[i]=toupper(buf[i]);}
	
					write(STDOUT_FILENO,buf,n);
					write(sockfd,buf,n);
			   	    }
			    }

			}

		}
	


	close(listenfd);
	close(efd);
	return 0;
}

//单机文件下载上传
//1.输入服务器地址（路径和目录名）
//2.列出服务器中有哪些文件（打开目录，读目录）
//3.输入要下载的文件名
//4.文件下载：IO，读写操作。
//打开源文件，新建目标文件，读出，写入。
//stract链接实现：server/fileload 组成新的文件名
//str0=stract(server,"/")
//str1=stract(str0,fileload)或
//stract（stract（server，“/”），fileload）返回字符串可以作为文件路径名
//src_fd=open(stract（stract（server，“/”），fileload） ， O_RDONLY);
	
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "dirent.h"
int main(){
struct dirent *dirent;
int src_fd;
int dec_fd;
char fileload[128]={0};
int rl;
char buf[128]={0};
char server[128]={0};
start:
printf( "input server name:\n");//输入文件夹路径
scanf("%s",server);

 DIR *dp;
 dp=opendir(server);
 
 if(dp==NULL){
   printf( "open server %s failure\n",server);
   goto start;
  }
  printf("open server sucess!\n");


  while(1){
  dirent=readdir(dp);//文件夹IO字符
  if(dirent!=NULL){
	printf("ino=%ld,name=%s\n",dirent->d_ino,dirent->d_name);//打印文件目录
   }
  else
    break;
 }

 printf("input filename:\n");//输入要下载的文件,注意是文件
 scanf("%s",fileload);


src_fd=open(strcat(strcat(server,"/"),fileload),O_RDONLY);//连接路径
if(src_fd<0){
 printf("open fileload failure\n");
 return -3;
}
printf("open fileload sucess\n");

dec_fd=open("decfile",O_CREAT|O_WRONLY,0777);//保存到defile
if(dec_fd<0){
 printf("creat decfile failure\n");
 return -2;
}
printf("craet decfile sucess");

while(1){
rl= read(src_fd,buf,128);
if(rl<128)
break;
write(dec_fd,buf,rl);
}
write(dec_fd,buf,rl);

close(src_fd);
close(dec_fd);
closedir(dp);

return 0;
}

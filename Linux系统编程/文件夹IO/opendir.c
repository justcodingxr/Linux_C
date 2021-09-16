//opendir  
//mkdir （“name”，权限）
//readdir struct dirent（d_ino,d_name)链表形式存，要循环读取
//rewinddir
//telldir
//seekdir
//closedir
	
#include "stdio.h"
#include "sys/types.h"
#include "dirent.h"
int main(int argc,char *argv[]){

        if(argc < 1){
        printf("error!");}

        DIR *dp;
        dp=opendir(argv[1]);
        if(dp == NULL){
        printf("open dir %s failure\n",argv[1]);
        return -0;}
        printf("open dir %s sucess\n",argv[1]);

        struct dirent *dirent;

        int i;
        i=0;
        while(1){
        dirent=readdir(dp);
        i++;
        //rewind(dp);回到表头
        //seekdir(dp,0)
        //if(i==5){
        //    seekdir(dp,0);
              i=0;
        //  }
	
        if(dirent != NULL){
        printf("ino=%ld,name=%s\n",dirent->d_ino,dirent->d_name);
        }
        else
            break;
        
    }
        closedir(dp);
        return 0;
}

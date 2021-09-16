//fgets和fputs
//   char *fgets(char *s,int size,FILE *stream )
//   返回值，成功s，尾端或出错，null
//将 buf[]="hello world"写入a.c		
#include "stdio.h"
int main(int argc,char *argv[]){
        FILE *fp;
        char buf[]="hello world";
        fp=fopen("a.c","w+");
        if(fp==NULL){
        printf("creat file failure");
        return -1;
        }
        printf("creat file  sucessfully ");
        fputs(buf,fp);

        fclose(fp);
        return 1;
}


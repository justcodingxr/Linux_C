#include "stdio.h"
int main(int argc,char *argv[]){
        FILE *fp;
        char buf[128]={0};
        fp=fopen("a.c","r");//w原内容删除
        if(fp==NULL){
        printf("creat file failure\n");
        return -1;
        }
        printf("creat file  sucessfully\n ");
        //fputs(fp,"ghjk");
        fseek(fp,0,SEEK_SET);//等价于rewind(fp)
        fgets(buf,128,fp);

        printf("%s\n",buf);
        fclose(fp);
        return 0;
}

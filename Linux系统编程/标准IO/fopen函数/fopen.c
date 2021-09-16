//标准io，间接调用系统调用，
//用户空间缓存，内核空间缓存，库缓存。
//printf遇到\n会将内容写入内容涵盖，或者库缓存写满；
//缓存	1024
//ftell(FILE *fp)获取当前文件位置
//fprintf可以输出到文件和显示器，printf只能输出到显示器。
//fprintf（fp，“ ”）；
//sprintf输出到一个字符串中；
//sprintf（str *," ");
//char bu[128];sprintf(buf,"sdsdw");
//fopen函数	
//open返回文件描述符，id号
//fopen返回文件流指针，
//r只读
//a\w创建，a追加，w原内容删除
//+读写
//b打开二进制文件
//权限：0666&（~umask）
//fopen打不开则创建
#include "stdio.h"
int main(int argc,char *argv[]){
	FILE *fp;
	fp=fopen(argv[1],"w+");//w+,r,等
	if(fp==NULL){
	printf("creat file %s failure",argv[1]);
	return -1;
	}
	printf("creat file %s  sucessfully ",argv[1]);
        fclose(fp);
	return 1;
}


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>


int main()
{      


//	char *cmd_list[]={"ls","-l",NULL};
	//命令参数列表，包括hello.sh,99.sh 和ls,pwd,ifconfig,ps,df,dmesg等命令
	char *cmd_list[]={"hello.sh",NULL,"99.sh",NULL,
						"df",NULL,"ifconfig",NULL,"ls","-a",NULL,"pwd",NULL,"ps",NULL,"dmesg",NULL};
	int len;
        char cmd[128];//存放命令
	while(1)
        {
                printf("[lingxr@localhost myshell]$ ");//提示符
                fflush(stdout);
               
				memset(cmd,0,sizeof(char)*128);//清空buf
				fgets(cmd,128,stdin);//输入命令
				
				len=strlen(cmd);
                if(len==1) continue;	//如果仅输>入换行符,提示重新输入,不退出
			
				if(cmd[len-1]=='\n')//换行继续，并替换\n为\0
                {
                        cmd[len - 1] = '\0';//'\0'读取数据流结束
                }
                len=strlen(cmd);

                pid_t id = fork();   //创建子进程
                if(id < 0)
                {
                        perror("fork");
                }
                else if(id == 0)
                {

                        execvp(cmd,cmd_list);   //将接收到的命令传给系统
                        exit(1);
                }
                else
                {
                        int status = 0;
                        pid_t ret = waitpid(id,&status,0);
                        if(ret > 0 && WIFEXITED(status))
                        {
                        printf("child process id:%d\n",ret);//返回子进程pid
                      }
                        else
                        {
                                perror("waitpid");//等待子进程执行
         }
                }
        }

        return 0;
}


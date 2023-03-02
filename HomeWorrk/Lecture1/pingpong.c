#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]){
	int p1[2],int p2[2];
	pipe(p1);
	pipe(p2);
	char buf[1]=" ";  
	if(fork()>0){ //父进程中
		close(p1[0]）;   //关闭p1读端
		close(p2[0]);	//关闭p2写端
		close(p2[1]);	//关闭p2读端	
		write(p1[1],buf,1)	//将buf的信号写入pipe中
		
		read(p2[0],buf,1);	//将信号从管道中读入到buf中
		printf("%d : received pong",gitpid());
		
		close(p1[1]);
		close(p2[0]);
		
		exit(0);
		
	}
	
	else if(fork() == 0){//子进程中
		close(p1[1]);	//关闭p1写端
		close(p2[0]);	//关闭p2读端
		read(p1[0], buf,1];	//从管道中读信号到buf中
		printf("%d : received ping",getpid());	//接收信号输出
		
		write(p2[1],buf,1);	//将信号从buf中写入到管道中
		
		close(p1[0]);
		close(p2[1]);
		exit(0);
		
		
		
	}
	
	else 
		exit(1)
	
	
}



#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	int p[2];
	pipe(p);
	char buf[2];
	
	if (fork()>0){
		close(p[0]); //关闭父进程管道读端
		for(int i=2;i<36;i++){
			if(i%2==0)
				continue;
			write(p[1],"0"+i,1);  //将buf中的数读入管道
			printf("primes : %d", 2);
		}
		wait(); //等待子程序执行完
		exit(0);	//退出
	}
	else if(fork()==0){
		close(p[1]);	//关闭子进程管道写端
		if(read(p[0],&buf[0],1)){
			
		};	//将管道中的数据读入buf[0]中
		while(read(p[1],&buf[1],1){
			
		}
		
		
	}
	else{
		exit(1);
	}
}

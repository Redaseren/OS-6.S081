#include "kernel/types.h"
#include "user/user.h"

#define PRIME_NUM 35

int main(int argc, char * argv[]){
	int p[2];
	char buf;
	pipe(p);
	
	if(fork()==0){//子进程中
		close(p[1]);	//关闭写端
		child(&p[0]);
		exit(0);
	}
	else{//最初的父进程中
		close(p[0]);  //关闭读端
		for(int i=2;i<PRIME_NUM+1;i++){
			write(p[1],"0"+i,1); //将初始数据写入管道中
		}
		
		close(p1[1]);
		wait(int*(0));
		
	}
	exit(0);
}

void child(int *p){
	int pr[2];
	char prime;
	if(read(p,&prime,1))
			printf("primes: %c\n",prime);
	else{
		exit(0); //没有数据可以读出，退出
	}
	
	
	if(fork()==0){//子进程中
		close(p);
		close(pr[1]);
		child(*pr[0]);
		close(pr[0]);
		exit(0);
	}
	
	else{//父进程中
		close(pr[0]);
		char buf;
		while(!read(p,&buf,1)){
			if(atoi(buf)%atoi(prime)==0){
				write(pr[1],buf,1);
			}
		}
		close(p);
		close(pr[1]);
		wait(int*(0));
		exit(0);
	}
}

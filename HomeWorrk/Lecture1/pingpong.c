#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]){
	int p1[2],int p2[2];
	pipe[p1];
	pipe[p2];
	char buf[1];  //restore signal;
	if(fork()!=0){ //enter parent process
		close(p1[1]）;   //关闭p1写端
		read(p1[0], 0 ,1);  //从标准输入里面写入信号
	}
	
	else if(fork()>0){
		
	}
	
	else 
		exit(1)
	
	
}



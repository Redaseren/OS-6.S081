#include "kernel/types.h" 
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]){
	if(argc == 1){
		//printf("Error Input");
		fprintf(2, "Error Input");
		exit(1);  //异常退出 
	}
	else{
		int num = atoi(argv[1]);  //将字符串转化为整数 
		sleep(num) ;
		exit(0);  //正常退出 
	}
	
}

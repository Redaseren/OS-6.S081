#include "kernel/types.h" 
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]){
	if(argc == 1){
		//printf("Error Input");
		fprintf(2, "Error Input");
		exit(1);  //�쳣�˳� 
	}
	else{
		int num = atoi(argv[1]);  //���ַ���ת��Ϊ���� 
		sleep(num) ;
		exit(0);  //�����˳� 
	}
	
}

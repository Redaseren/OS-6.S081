#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	int p[2];
	pipe(p);
	char buf[2];
	
	if (fork()>0){
		close(p[0]); //�رո����̹ܵ�����
		for(int i=2;i<36;i++){
			if(i%2==0)
				continue;
			write(p[1],"0"+i,1);  //��buf�е�������ܵ�
			printf("primes : %d", 2);
		}
		wait(); //�ȴ��ӳ���ִ����
		exit(0);	//�˳�
	}
	else if(fork()==0){
		close(p[1]);	//�ر��ӽ��̹ܵ�д��
		if(read(p[0],&buf[0],1)){
			
		};	//���ܵ��е����ݶ���buf[0]��
		while(read(p[1],&buf[1],1){
			
		}
		
		
	}
	else{
		exit(1);
	}
}

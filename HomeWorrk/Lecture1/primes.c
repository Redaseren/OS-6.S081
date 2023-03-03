#include "kernel/types.h"
#include "user/user.h"

#define PRIME_NUM 35

int main(int argc, char * argv[]){
	int p[2];
	char buf;
	pipe(p);
	
	if(fork()==0){//�ӽ�����
		close(p[1]);	//�ر�д��
		child(&p[0]);
		exit(0);
	}
	else{//����ĸ�������
		close(p[0]);  //�رն���
		for(int i=2;i<PRIME_NUM+1;i++){
			write(p[1],"0"+i,1); //����ʼ����д��ܵ���
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
		exit(0); //û�����ݿ��Զ������˳�
	}
	
	
	if(fork()==0){//�ӽ�����
		close(p);
		close(pr[1]);
		child(*pr[0]);
		close(pr[0]);
		exit(0);
	}
	
	else{//��������
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

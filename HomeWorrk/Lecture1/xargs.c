//xargs程序的作用是将输入转化为后面要执行的命令行参数

//*****************注意*******************
//通过管道得来的数据会转化为一个字符串，而该字符串可能包含多个命令行参数，
//因此必须对这个字符串进行处理

/*对标准输入每次读一个char，若读到\n需要执行命令。注意在执行xargs这个
命令行的时候，最后肯定要按一个回车，这时标准输入最后会有一个回车，
所以在EOF前是会有一个回车的！！！*/


#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLEN 100

int main(int argc, char *argv[]){
	if(argc < 1){
		fprintf(2,"Just one parameter");
		exit(1);
	}
	
	char param[MAXARG][MAXLEN]; //存储命令行参数
	int count =0;	//命令行参数的个数
	char now[MAXLEN];	//指向即将要处理的字符串
	
	memset(param,0,MAXARG*MAXLEN);
	
	for(int i =1;i<argc;i++){
		memset(now,0,MAXLEN);
		memmove(now,argv+i,strlen(argv+i));
		int k=0;
		int flag =0; //标志是否是另一个命令
		for(int j=0;j<strlen(now);j++){
			if(now[j]==' '){
				if(flag ==1)
					count++;
				flag = 0;
				k=0;
				continue;
			}
		
			else if(now[j]=='\n' || now[j]== EOF || now[j]== '\0')	//读到命令行或者文件结尾
			//此处不会有'\0',因为strlen函数不包括字符串结尾
				break;
			
			else{
				param[count][k++] = now[j];
				flag=1;
			}
			
		}
	}
	
	
	for(int i=2;i<argc;i++){
		if(fork()==0){
			exec(param[1],param[i]);
		}
		else {
			wait();
			exit(0);
		}
	}
}

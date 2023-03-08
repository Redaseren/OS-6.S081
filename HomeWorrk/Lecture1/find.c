#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"


int main(int argc, char *argv[]){
	if(argc<3){
		fprintf(2,"ERROR INPUT\n");
		exit(1);
	}
	for(int i=1;i<argc;i++){
		find(argv[1],argv[i+1]);
	}
}



//获得路径中最后一个'/'后的文件名
char*
fmtname(char *path){
	static char buf[DIRSIZE+1];
	char *p;
	
	//将p指向buf最后一个字节，即'\0'
	p=path+strlen(path);
	//找到最后一个'/'后的第一个字符指向的指针
	while(p !='/'&&p >= path){
		p--;
	}
	p++;
	
	// Return blank-padded name.
	if(strlen(p) >= DIRSIZE)
		return p;
	
	//将字符拷贝进入buf中
	memmove(buf, p, strlen(p));	
	
	//初始化buf中剩下的内存
	//*******感觉有点问题，空字符有'\0',0,''三种表示方法********
	memset(buf+strlen(p),' ',DIRSIZE-strlen(p));
	return buf;
	
}


void find(char *path, char *target_file){
	int fd;
	char buf[512], *p;
	struct dirent de;
	struct stat st;
	
	if(fd =open(path,0)<0){
		fprintf(2,"Can't open this path");
		return;
	}
	
	//判断能否存储文件信息，如果能，则存储
	if(fstat(fd, &st)< 0){
		 fprintf(2, "ls: cannot stat %s\n", path);
		close(fd);
		return;
	}
	
	switch(st.type){
		case T_DEVICE:
		case T_FILE:
			if(!strcmp(fmtname(path),fmtname(target_file))
				printf("%s\n",path);
			break;
		case T_DIR:
			if(strlen(path)+1+DIRSIZE+1 > sizeof buf){
				printf("Path is too long");
				break;
			}
			
			while(read(fd,&de,sizeof de)== sizeof de){
				
				//输出绝对路径？
				//strcpy(buf, path);
				memmove(p, path, strlen(path));	
				p=buf+strlen(buf);
				*p++='/';
				memmove(p,de.name,DIRSIZE);
				p[DIRSIZE]=0;
				find(buf,targetfile);
			}
			break;
	}
	close(fd);
	return;
}
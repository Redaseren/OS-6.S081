#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


//fmtname()函数的作用是取出路径中最后一个斜杠里的文件名
char*
fmtname(char *path)
{
  //注意静态变量的作用
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));	//将p所指的strlen（p）个字节复制到buf中
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));	
  //将buf中长度为strlen（p）后的字符初始化为' '字符
  //最后一个字符（应该为'\0'）没有被' '初始化
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0	//返回文件信息，并储存到st指向的结构中
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_DEVICE:	//设备文件
  case T_FILE:	//文件
    printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);	//将path字符串复制到buf中
    p = buf+strlen(buf);	//将p指针指向buf中的最后一位
    *p++ = '/';	//++优先级低于解引用运算符*
	//此处首先向buf[strlen(buf)]变为'/',也就是buf中原来为'\0'的位置
	//将p右移一位：将p指针加1，指向与buf最后一位相邻的位置
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
	//将fd文件或者目录中的信息读入de中去，
	//如果读到的字节不是de所指结构体的大小，
	//代表读完了，或者一开始就不可读
      if(de.inum == 0)
        continue;
	
	//********不懂*********
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
	  
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit(0);
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit(0);
}

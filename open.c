/*===============================================
*   文件名称：open.c
*   创 建 者：     
*   创建日期：2026年04月14日
*   描    述：
================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{ 
    int fd;//文件描述符
    //打开

    fd = open("1.txt",O_RDWR | O_CREAT, 0664);//110 110 100
    if(-1 == fd){
        //打开失败
        perror("open fail\n");
        return -1;

    }

    printf("fd is %d\n",fd);

    size_t  ret;
    char buf[1024] = {0};

    lseek(fd,2,SEEK_SET);

    ret = read(fd,buf,8);

    if(ret == -1){

        perror("read fail\n");
        return -1;
    }
    printf("%s\n",buf);
    lseek(fd,-2,SEEK_END);

    char buf1[64] = "芝麻酥";
    size_t ret1;

    ret1 = write(fd,buf1,64);
    if(ret1 == -1){
        perror("write fail\n");
        return -1;
    }

    close(fd);
    return 0;
}


/*===============================================
*   文件名称：client.c
*   创 建 者：     
*   创建日期：2026年01月09日
*   描    述：gcc -o client client.c
================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 8000 // 与server.c中定义的PORT保持一致
#define SERVER_IP "127.0.0.1" // 服务器IP地址，默认连接本机
#define BUF_SIZE 1024 // 定义缓冲区大小

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    // 1. 创建套接字
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }
    printf("客户端套接字创建成功.\n");

    // 2. 设置服务器地址信息
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    // 转换IP地址格式
    if(inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("地址错误或者地址不支持\n");
        return -1;
    }

    // 3. 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("连接失败\n");
        return -1;
    }
    printf("连接到服务器 %s:%d\n", SERVER_IP, SERVER_PORT);

    printf("可以发送信息 (输入 'exit' 退出):\n");
    
    // 4. 通信循环
    while(1) {
        char message[BUF_SIZE];
        printf("请输入发送给服务器的消息: ");
        fgets(message, BUF_SIZE, stdin);
        // 去除换行符
        message[strcspn(message, "\n")] = '\0';

        // 输入exit则退出
        if (strcmp(message, "exit") == 0) {
            printf("客户端主动退出\n");
            break;
        }

        // 发送消息给服务器
        send(sock, message, strlen(message), 0);
        printf("消息已发送: %s\n", message);

        // 清空缓冲区并接收服务器回复
        memset(buffer, 0, BUF_SIZE);
        ssize_t valread = read(sock, buffer, BUF_SIZE);
        if (valread <= 0) {
            printf("服务器断开连接\n");
            break;
        }

        printf("收到服务器回复: %s\n", buffer);
    }

    // 5. 关闭套接字
    close(sock);
    printf("连接已关闭.\n");
    return 0;
}

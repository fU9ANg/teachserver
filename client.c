#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#include <Protocol.h>
#define SERV_IP "127.0.0.1"
#define SERV_PORT 9999 
#define CON_NUM 10


int main(int argc, char* argv[]){
    int cntFd[CON_NUM] = {0};
    int i = 0;
    for( i = 0; i< CON_NUM; ++i) {
        cntFd[i] = socket(AF_INET, SOCK_STREAM, 0);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERV_IP);
    addr.sin_port = htons(SERV_PORT);

    for( i = 0; i< CON_NUM; ++i) {
        connect(cntFd[i], (struct sockaddr*)&addr, sizeof(struct sockaddr));
    }
    while(1) {
        sleep(1);
        printf("xxxx\n");
        struct msg x;
        x.len = sizeof(struct msg) - sizeof(int);
        strcpy(x.buf, "hellow");
        for( i = 0; i< CON_NUM; ++i) {
            send(cntFd[i], &x, sizeof(x), 0);
        }
    }

    for( i = 0; i< CON_NUM; ++i) {
        close(cntFd[i]);
    }

    return 0;
}

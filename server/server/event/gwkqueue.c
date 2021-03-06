//
//  gwkqueue.c
//  server


#include "gwkqueue.h"

#include "gwconnection.h"
#include "gwpool.h"

#define MAX_EVENT_COUNT 5000
const static int FdNum = 2;         // 两个文件描述符


int
initKqueue(){
    int fd = kqueue();
    if (fd < 0) {
        quit("kevent()");
    }
    return fd;
}


// Register 将 fd 注册到 kq 中。
// 注册的方法是通过 kevent() 将 eventlist 和 neventlist 置成 NULL 和 0 来达到的。
bool
GwKqueueAddListener(int kq, int fd) {
    struct kevent changes[1];
    EV_SET(&changes[0], fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    
    // changelist: 要注册 / 反注册的事件数组； nchanges: changelist 的元素个数
    int ret = kevent(kq, changes, 1, NULL, 0, NULL);
    return true;
}


void
Accept(int kq, int connSize, GwConnection *conn) {
    int socketFile = conn->server;
    
    for (int i = 0; i < connSize; i++) {
        int client = accept(socketFile, NULL, NULL);
        // 将 accept 成功的 socket 注册到 kq
        GwKqueueAddListener(kq, client);
    }
}


void
Receive(int sock, int availBytes) {
    // todo 加入缓冲队列 EVFILT_WRITE
    GwConnResponse(&sock);
}


void
ReceiveHttps(int sock, GwConnection *conn) {
    SSL_CTX *ctx = conn->ctx;
    SSL *ssl = SSL_new(ctx);
    
    SSL_set_fd(ssl, sock);
    Servlet(ssl);
    close(sock);
}


void
GwKqueueHandleEvent(int kq, struct kevent* events, int nevents, GwConnection *conn) {
    int socketFile = conn->server;
    
    for (int i = 0; i < nevents; i++) {
        int sock = events[i].ident;
        // 对于监听 socket, data 表示连接完成队列中的元素 ( 已经收到三次握手最后一个 ACK) 个数
        // 对于流 socket，data 表示协议栈 socket 层的接收缓冲区可读数据的字节数
        int data = events[i].data;
        
        printf("sock data %d %d %d\n", sock, data, getpid());
        if (sock == socketFile) {
            Accept(kq, data, conn);
        } else {
            // http or https
            if (conn->protocol == EnumProtocolHttp) {
                printf("http\n");
                Receive(sock, data);
            } else if (conn->protocol == EnumProtocolHttps) {
                printf("https\n");
                ReceiveHttps(sock, conn);
            } else {
                printf("unknow protocol\n");
            }
        }
    }   
}





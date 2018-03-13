//
//  main.c
// cc *.c -Ilua-5.3.4/src -llua -Llua-5.3.4/src && ./a.out
// test:  siege -c 100 -r 10 http://127.0.0.1:3000/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#include <pthread.h>
//#include <stdbool.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <sys/types.h>

#include "threadpool.h"
#include "gwsocket.h"
#include "gwkqueue.h"
#include "config.h"
#include "master.h"
#include "worker.h"
#include "gwpipe.h"

int
main(int argc, const char *argv[]) {
    
    int *fd = GwPipeInit();
    pid_t id = fork();
    if (id < 0) {
        quit("fork()");
    } else if (id == 0) {
        // child
        GwPipeClose(fd, EGwPipeRead);
        int i = 0;
        char *msg = NULL;
        while (i < 100) {
            msg = "I am child";
            GwPipeWrite(fd, msg, strlen(msg));
            sleep(1);
            i++;
        }
        
    } else {
        // parent
         GwPipeClose(fd, EGwPipeWrite);
        int j = 0;
//        char rsp[100];
        while (j < 100) {
            char *rsp = GwPipeRead(fd);
            printf("parent: %s\n", rsp);
            j++;
        }
    }
//    GwStartMaster();
    
//    int epollfd = initKqueue();
//    initLuaEnv();
//
//    // socket
//    unsigned int port = 3000;
//    int s = openSocket(port);
//    setNonBlock(s);
//
//    struct sockaddr_in client;
//    int size = sizeof(struct sockaddr_in);
//
//    // 注册事件
//    updateEvents(epollfd, s, GwKQueueFilterRead | GwKQueueFilterWrite, GwKQueueFlagAdd);
//
//
//    int numOfPid = 4;
//    pid_t pid;
//    for (int i = 0; i < numOfPid; i++) {
//        pid = fork();
//        if (pid == 0 || pid == -1) {
//            break;
//        }
//    }
//
//    if (pid < 0) {
//        quit("fork()");
//    } else if (pid == 0) {
//        // chlidren
//        GuaThreadPool *pool = GuaThreadPoolNew(5);
////        GuaThreadPoolAddTask(pool, response, n);
//        while (true) {
//            loopOnce(epollfd, s, 10000, pool);
//        }
//        printf("chlid %d\n", getpid());
//    } else {
//        // parents
//        wait(NULL);  // 等待子进程退出
//        printf("parents %d\n", getpid());
//    }
//
//    closeLuaEnv();

    return 0;
}

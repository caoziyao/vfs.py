//
//  input_kqueue.h
//  server
//
//  Created by working on 2018/3/12.
//  Copyright © 2018年 working. All rights reserved.
//

#ifndef input_kqueue_h
#define input_kqueue_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/event.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int
inputKqueue();

#endif /* input_kqueue_h */

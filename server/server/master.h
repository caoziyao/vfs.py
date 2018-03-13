//
//  master.h
//  server
//
//  Created by working on 2018/3/13.
//  Copyright © 2018年 working. All rights reserved.
//

/*
 master进程管理worker进程
 1, 接收来自外界的信号
 2, 向各worker进程发送信号
 3, 监控worker进程的运行状态
 4, 当worker进程退出后(异常情况下)，会自动重新启动新的worker进程
 
 */

#ifndef master_h
#define master_h

#include <stdio.h>
#include "config.h"

// 启动worker进程
void
GwStartMaster();

#endif /* master_h */
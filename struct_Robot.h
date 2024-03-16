#ifndef STRUCT_ROBOT_H//预定义避免重复引入
#define STRUCT_ROBOT_H

#define ROBOT_STUCK -1
#define ROBOT_IDLE 0
#define ROBOT_GETTING 1
#define ROBOT_SENDING 2

#define MOVE_RIGHT 0
#define MOVE_LEFT 1
#define MOVE_UP 2
#define MOVE_DOWN 3

#include "list.h"
typedef struct Robot
{
    int x, y;//目前位置
    int goods;//？
    int status;//状态 取货robot_getting 送货robot_sending 受困robot_stuck
    int direct;//下一步方向
}Robot;

#endif
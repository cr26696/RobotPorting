#ifndef STRUCT_ROBOT_H//预定义避免重复引入
#define STRUCT_ROBOT_H

#define ROBOT_STUCK -1//困住
#define NORMAL 0 //正常
#define ROBOT_GETTING 1//取货
#define ROBOT_SENDING 2//送货
#define ROBOT_CRASHING 3//碰撞
#define ROBOT_VOIDING 4//避让

#define MOVE_RIGHT 0
#define MOVE_LEFT 1
#define MOVE_UP 2
#define MOVE_DOWN 3

#include "list.h"
#include "geometry.h"

typedef struct Robot
{
    Point pos;//目前位置
    int current_status;//当前状态 
    int next_status;//下一帧状态 
    int direct;//下一步方向
}Robot;

#endif
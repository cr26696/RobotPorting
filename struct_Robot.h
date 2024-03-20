#ifndef STRUCT_ROBOT_H//预定义避免重复引入
#define STRUCT_ROBOT_H

// #define ROBOT_STUCK -1//困住
// #define ROBOT_FREE 0 //空闲
// #define ROBOT_GETTING 1//取货
// #define ROBOT_SENDING 2//送货
// #define ROBOT_CRASHING 3//碰撞
// #define ROBOT_VOIDING 4//避让


#define MOVE_RIGHT 0
#define MOVE_LEFT 1
#define MOVE_UP 2
#define MOVE_DOWN 3
#define ROBOT_WAITING 4

#include "geometry.h"

typedef enum {
    STUCK = -1,//困住
    IDLE = 0, //空闲
    GETTING = 1,//取货路上
    SENDING = 2,//送货路上
    CRASHING = 3,//碰撞
    VOIDING = 4,//避让
    GET = 5,//下一步移动取货
    SEND = 6//下一步移动送货
}robot_state;

typedef struct Robot
{
    Point pos;//目前位置
    robot_state current_status;//当前状态
    robot_state next_status;//下一帧状态
    robot_state tempstatus;//碰撞前的状态暂存
    int direct;//下一步方向
}Robot;

#endif
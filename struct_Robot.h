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
#include "LinkPath.h"

typedef enum {
    STUCK = -1,//困住
    IDLE = 0, //空闲
    GETTING = 1,//取货路上
    SENDING = 2,//送货路上
    CRASHING = 3,//碰撞
    VOIDING = 4,//避让
    SearchBerth = 5,//准备找泊口
    SearchParcel = 6,//准备找货物
    GET = 7,//拿货
    PULL = 8//放货
}robot_state;

// typedef enum {
//     MOVE_RIGHT = 0,
//     MOVE_LEFT = 1,
//     MOVE_UP = 2,
//     MOVE_DOWN = 3,
//     ROBOT_WAITING = 4,
//     GETTING = 5,//取货路上
//     SENDING = 6,//送货路上
//     VOIDING = 7,//避让
//     SearchBerth = 5,//准备找泊口
//     SearchParcel = 6,//准备找货物
//     GET = 7,//拿货
//     PULL = 8//放货
// }robot_action;

typedef struct Robot
{
    int id;
    Point pos;//目前位置
    Point aim;//最终目标地点
    LinkPath* curPath;
    robot_state current_status;//当前状态
    robot_state next_status;//下一帧状态
    robot_state tempstatus;//碰撞前的状态暂存
    int moveDirect;//机器人行动
}Robot;

#endif
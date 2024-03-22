#ifndef STRUCT_ROBOT_H//预定义避免重复引入
#define STRUCT_ROBOT_H

#include "geometry.h"
#include "LinkPath.h"

#define TimeLimit 10

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
typedef struct Robot
{
    int id;
    int reLocCount;//重定位计时 大概30帧后重新寻路
    Point pos;//目前位置
    Point aim;//最终目标地点 可能是货物货泊口
    int aimBerth;//目标泊口
    LinkPath* curPath;//存储当前道路
    robot_state current_status;//当前状态
    robot_state next_status;//下一帧状态
    robot_state tempstatus;//碰撞前的状态暂存
    direction moveDirect;//机器人行动
}Robot;

#endif
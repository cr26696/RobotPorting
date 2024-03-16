#ifndef STRUCT_ROBOT_H//预定义避免重复引入
#define STRUCT_ROBOT_H

// #define ROBOT_STUCK -1//困住
// #define huiffu 0 //???
// #define ROBOT_GETTING 1
// #define ROBOT_SENDING 2

#define MOVE_RIGHT 0
#define MOVE_LEFT 1
#define MOVE_UP 2
#define MOVE_DOWN 3

#include "list.h"
#include "geometry.h"

typedef struct Robot
{
    Point pos;//目前位置
    int goods;//0携带物品，送货
    int status;//状态 
    int stuck;//0不受困；1受困
    int direct;//下一步方向
}Robot;

#endif
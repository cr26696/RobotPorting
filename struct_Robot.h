#ifndef STRUCT_ROBOT_H//预定义避免重复引入
#define STRUCT_ROBOT_H

typedef struct Robot
{
    int x, y, goods;
    int status;
    int mbx, mby;
}Robot;

#endif
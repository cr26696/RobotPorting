#ifndef STRUCT_BOAT_H//预定义避免重复引入
#define STRUCT_BOAT_H

typedef struct Boat
{
    //int num;//标号
    int aimId;//目标泊位，虚拟点是-1
    int status;//状态,0运输，1装货或运输完，2等待
    int goodsnum;//船上货物数量
}Boat;

#endif
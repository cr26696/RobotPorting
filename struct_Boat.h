#ifndef STRUCT_BOAT_H//预定义避免重复引入
#define STRUCT_BOAT_H

#define TRANSPORT 0//从泊口到虚拟点途中
#define ATVIRTUAL 1//到达虚拟点
#define GOBACKBERTH 2//从虚拟点到泊口途中
#define ATBERTH 3//到泊口，装载
#define WAITING 4//到泊口等待(前面还有其他船)

typedef struct Boat
{
    //int num;//标号
    int aimId;//目标泊位，虚拟点是-1
    int status;//当前状态(自己维护)
    // int priorstatus;//之前的状态
    int goodsnum;//船上货物数量
}Boat;

#endif
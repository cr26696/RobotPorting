#ifndef STRUCT_BOAT_H//预定义避免重复引入
#define STRUCT_BOAT_H

#define TRANSPORT 0//从泊口到虚拟点途中
#define ATVIRTUAL 1//到达虚拟点
#define GOBACKBERTH 2//从虚拟点到泊口途中
#define ATBERTH 3//到泊口
#define WAITING 4//到泊口等待(前面还有其他船)
#define NOLOADING 5//到泊口，空闲
#define LOADING 6//到泊口，装载
#define FINISHLOADING 7//到泊口，装载完
typedef struct Boat
{
    //int num;//标号
    int aimId;//目标泊位，虚拟点是-1
    int status;//当前状态(自己维护)
    int priorstatus;//之前的状态
    int goodsnum;//船上货物数量
}Boat;

void controlBoat(Boat *boat[],int boat_num,Berth *berth[],int berth_num,int boat_capacity);
void countgoodsnum(Berth *berth,Boat *boat);//计算泊口的货物数量和船上的货物数量
#endif
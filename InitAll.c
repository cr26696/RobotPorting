#include "InitAll.h"

void InitRobot(Boat *robot[],int robot_num)//机器人状态初始化???判断是否受困
{
    for(int i=0;i<robot_num;i++){
		robot[i].
        
        //aStarSearch(&map,robot[i].)
	}
}

void InitBerth(Berth *berth[],int berth_num)//泊口状态初始化
{
 for(int i = 0; i < berth_num; i ++)
 {
    berth[i]->goodsnum=0;
    berth[i]->status=1;
 }
}

void InitRoat(Boat *boat[],int boat_num)//船状态初试化让他从虚拟点到泊口
{
    for(int i = 0; i < boat_num; i ++)
 {
    boat[i]->aimId=-1;
    boat[i]->status=ATVIRTUAL;
    boat[i]->goodsnum=0;
 }
}

void Inittotal(Boat *robot[],int robot_num,Boat *boat[],int boat_num,Berth *berth[],int berth_num,int boat_capacity )
{
    InitRobot(boat,robot_num);
    InitBerth(berth,berth_num);
    InitRoat(boat,boat_num);
    controlBoat(boat,boat_num,berth,berth_num,boat_capacity);
}
#include "InitAll.h"

#include "astar.h"

void Inittotal(Robot robot[],int robot_num,Boat boat[],int boat_num,Berth berth[],int berth_num,int boat_capacity )
{
    InitRobot(robot,robot_num);
    InitBerth(berth,berth_num);
    InitRoat(boat,boat_num);
    controlBoat(boat,boat_num,berth,berth_num,boat_capacity);
}

void InitRobot(Robot robot[],int robot_num)//机器人状态初始化???判断是否受困
{
    extern Map map;
    extern Berth berth[];
    for(int robotId=0;robotId<robot_num;robotId++){
        LinkList *hasPath;
		for(int berthId;berthId<10;berthId++){//遍历泊口看能不能到
            hasPath = aStarSearch(&map,robot[robotId].pos,berth[berthId].pos);
            if(hasPath){break;}
        }
        if(hasPath){continue;}
        else{
            robot[robotId].current_status=STUCK;
            robot[robotId].next_status=STUCK;
        }
        robot[robotId].current_status=IDLE;
        robot[robotId].next_status=IDLE;
        robot[robotId].direct=ROBOT_WAITING;
        //aStarSearch(&map,robot[i].)
	}
}

void InitBerth(Berth berth[],int berth_num)//泊口状态初始化
{
 for(int i = 0; i < berth_num; i ++)
 {
    berth[i].goodsnum=0;
    berth[i].status=1;
 }
}

void InitRoat(Boat boat[],int boat_num)//船状态初试化让他从虚拟点到泊口
{
    for(int i = 0; i < boat_num; i ++)
 {
    boat[i].aimId=-1;
    boat[i].status=ATVIRTUAL;
    boat[i].goodsnum=0;
 }
}
//为货物地图赋值0，为货物计时链表赋值
void InitParcel(Map *ParcelMap, LinkParcel *linkParcel){
    //货物分布地图初始化
    for(int i;i<200;i++){
        for(int j;j<200;j++){
            ParcelMap->data[i][j] = '0';
        }
    }

    //货物计时链表初始化(分配内存空间)
    linkParcel = LinkInit_Parcel(linkParcel);
}
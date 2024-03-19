#include "InitAll.h"

#include "astar.h"
#include "Boat.h"

void Inittotal(Map map,Robot robots[],int robotCount,Boat boats[],int boatCount,Berth berths[],int berthCount,int boat_capacity )
{
	InitBerth(berths,berthCount);
	InitBoat(boats,boatCount);
	controlBoat(boats,boatCount,berths,berthCount,boat_capacity);
	InitRobot(map,berths,berthCount,robots,robotCount);
}

void InitRobot(Map map,Berth berths[],int berthCount,Robot robots[],int robotCount)//机器人状态初始化???判断是否受困
{
	LinkList *hasPath;
	for(int robotId=0;robotId<robotCount;robotId++){//遍历机器人
		for(int berthId;berthId<berthCount;berthId++){//遍历泊口看能不能到
			hasPath = aStarSearch(&map,robots[robotId].pos,berths[berthId].pos);
			if(hasPath){break;}
		}
		if(hasPath){//机器人不受困
			deleteLink_Grid(hasPath);
			robots[robotId].current_status=IDLE;
			robots[robotId].next_status=IDLE;
			robots[robotId].direct=ROBOT_WAITING;
		}
		else{//机器人受困，设置状态
			robots[robotId].current_status=STUCK;
			robots[robotId].next_status=STUCK;
		}
		deleteLink_Grid(hasPath);
	}
}

void InitBerth(Berth berths[],int berth_num)//泊口状态初始化
{
 for(int i = 0; i < berth_num; i ++)
 {
	berths[i].goodsnum=0;
	berths[i].status=1;
 }
}

void InitBoat(Boat boats[],int boatCount)//船状态初试化让他从虚拟点到泊口
{
	for(int i = 0; i < boatCount; i ++)
	{
		boats[i].aimId=-1;
		boats[i].status=ATVIRTUAL;
		boats[i].goodsnum=0;
	}
}
//为货物地图赋值0，为货物计时链表赋值 全局只调用一次
void InitParcel(Map *ParcelMap, LinkParcel *pLinkParcel, LinkParcel *pLockedParcels){
	//货物分布地图初始化
	for(int i;i<200;i++){
		for(int j;j<200;j++){
			ParcelMap->data[i][j] = '0';
		}
	}
	//货物计时链表初始化(分配内存空间)
	pLinkParcel = LinkInit_Parcel(pLinkParcel);

	//锁定货物数组初始化
	pLockedParcels = LinkCreate_Parcel(10);
}
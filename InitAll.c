#include "InitAll.h"

void Inittotal(Map map,Grid** gridMap,Robot robots[],int robotCount,Boat boats[],int boatCount,Berth berths[],int berthCount,int boat_capacity )
{
	InitBerth(berths,berthCount);
	InitBoat(boats,boatCount);
	for (int i=0;1<boatCount;i++)
	{
		BoatAtVIRTUAL(&boats[i],boatCount,berths,berthCount);
		printf("ship %d %d\n", i, boats[i].aimId);
	}
	InitRobot(map,gridMap,berths,berthCount,robots,robotCount);
}

void InitRobot(Map map,Grid** gridMap, Berth berths[],int berthCount,Robot robots[],int robotCount)//机器人状态初始化???判断是否受困
{//默认地图大小200;
	int tRobotID=0;//读地图机器人序号
	for(int mx=0;mx<200 && tRobotID<10;mx++){
		for(int my=0;my<200 && tRobotID<10;my++){
			if(map.data[mx][my] =='A'){
				robots[tRobotID].pos = createPoint(mx,my);
				tRobotID++;
			}
		}
		if(tRobotID>=10) break;
	}
	LinkPath *hasPath = NULL;
	for(int i=0;i<10;i++){
		robots[i].id = i;
	}
	for(int i=0;i<robotCount;i++){//遍历机器人
		// for(int berthId=0;berthId<berthCount;berthId++){//遍历泊口看能不能到 <- 扫一个就行
		// hasPath = aStarSearch(&map,robots[robotId].pos,berths[0].pos);
		// if(hasPath){break;}
		
		if(!isStuck(robots[i].pos,35)){//机器人不受困
			robots[i].current_status=IDLE;
			robots[i].next_status=SearchParcel;
			// robots[robotId].moveDirect=-1;
		}
		else{//机器人受困，设置状态
			robots[i].current_status=STUCK;
			robots[i].next_status=STUCK;
		}
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
void InitParcel(LinkParcel *pLinkParcel, LinkParcel *pLockedParcels){
	//货物分布地图初始化
	for(int i;i<200;i++){
		for(int j;j<200;j++){
			parcelMap[i][j].value = 0;
		}
	}
	//货物计时链表初始化(分配内存空间)
	pLinkParcel = LinkInit_Parcel(pLinkParcel);

	//锁定货物数组初始化
	pLockedParcels = LinkCreate_Parcel(10);
}
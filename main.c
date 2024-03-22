#include <stdio.h>
#include <stdlib.h>


#include "moveControl.h"
#include "astar.h"

#include "struct_Map.h"
#include "struct_Robot.h"
#include "struct_Berth.h"
#include "struct_Boat.h"
#include "struct_Grid.h"

#include "Robot.h"
#include "Boat.h"

#include "InitAll.h"

#define MAPSIZE 200
#define robot_num 10
#define berth_num 10
#define boat_num 5
#define N 200


// Map parcelMap;//同上
Map map;//内有200x200 char数组
Parcel parcelMap[200][200] = {0};//同上
Grid gridMap[200][200];
//Parcel parcelMap[200][200];

Robot robot[robot_num];//<----不当全局变量的话 建议写main()里面
Berth berth[berth_num];
Boat boat[boat_num];

Point toAvoid[20];//需要避让的点 最多20
int toAvoidLen;

LinkParcel LinkParcels;
LinkParcel LockedParcels;

LinkPath paths_robot[robot_num];//调用起来

int money, boat_capacity, frame;
int numofgds = 0;

void Init()
{
		numofgds = 0;
		for(int i = 0; i < MAPSIZE; i ++)
		{
			scanf("%s",map.data[i]);
		}

		for(int i = 0; i < berth_num; i ++)
		{
				int id;
				scanf("%d", &id);
						berth[id].id=id;
				scanf("%d%d%d%d", &berth[id].pos.x, &berth[id].pos.y, &berth[id].transport_time, &berth[id].loading_speed);
		}

		scanf("%d", &boat_capacity);//???
		char okk[100];

		scanf("%s", okk);
		//???我们定义的初始化数据(机器人状态，船、泊口初始化，让船到泊口)

		InitBerth(berth,berth_num);
		InitBoat(boat,boat_num);
		InitRobot(map,(Grid**)gridMap,berth,berth_num,robot,robot_num);
		InitParcel(&LinkParcels, &LockedParcels);
		printf("OK\n");//初始化结束
		fflush(stdout);
}

int Input()
{
		scanf("%d%d", &frame, &money);//帧数和当前金额
		int newParcels;//新增货物数量
		scanf("%d", &newParcels);//???
		for(int i = 1; i <= newParcels; i ++)
		{
				int x,y,val;
				scanf("%d%d%d", &x, &y, &val);
				//读取到货物结构体
				parcelMap[x][y] = createParcel(x,y,frame,val);
				LinkInsertEnd_Parcel(&LinkParcels,parcelMap[x][y]);
				numofgds ++;
		}
		for(int i = 0; i < robot_num; i ++)
		{
				int carry,awake;//carry：0表示未携带物品；awake:0表示恢复状态(晕眩)
				scanf("%d%d%d%d", &carry, &robot[i].pos.x, &robot[i].pos.y, &awake);
				robotUpdate_sysInput(carry,awake,&robot[i]);//机器人状态处理函数
				// robot[i].current_status = robot[i].next_status;
		}
		for(int i = 0; i < 5; i ++)
		{
			int backstatus,aimId;//判决器返回状态,目标泊口
			scanf("%d%d", &backstatus, &aimId);
			boatStatusupdate(backstatus,aimId,&boat[i]);//船状态处理函数
		}
		char okk[100];

		//避让点初始化
		toAvoidLen = 10;
		for(int i=0;i<robot_num;i++){
			toAvoid[i].x = robot[i].pos.x;
			toAvoid[i].y = robot[i].pos.y;
		}

		scanf("%s", okk);
		return frame;
}

int main()
{ 
	Init();
	for(int frame = 1; frame <= 15000; frame ++)
	{
		frame = Input();//返回当前帧数
		for(int i = 0; i < robot_num; i ++)//机器人控制
		{
			robotUpdate_Action(&robot[i]);
			robotAction(&robot[i]);
			robot[i].current_status = robot[i].next_status;
		}
		if(frame==1){
			for(int i=0;i<boat_num;i++){
			BoatAtVIRTUAL(&boat[i],boat_num,berth,berth_num);
			printf("ship %d %d\n", i, boat[i].aimId);
			}
		}else controlBoat(boat,boat_num,berth,berth_num,boat_capacity);//对船进行操作	
		//消失货物列表维护
		if(frame>1000)ParcelTimedDelete(&LinkParcels,frame);
		puts("OK");
		fflush(stdout);
	}

	return 0;
}

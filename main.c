#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "moveControl.h"
#include "astar.h"

#include "struct_Map.h"
#include "struct_Robot.h"
#include "struct_Berth.h"
#include "struct_Boat.h"

#include "Robot.h"
#include "Boat.h"

#include "InitAll.h"


#define n 200
#define robot_num 10
#define berth_num 10
#define boat_num 5
#define N 200

int numofgds = 0;


// struct Robot
// {
//     int x, y, goods;
//     int status;
//     int mbx, mby;
// }robot[robot_num];
// struct Berth
// {
		// int x;a
		// int y;
		// int transport_time;
		// int loading_speed;
// }berth[berth_num];
// struct Boat
// {
//     int num, pos, status;
// }boat[boat_num];

Map map;//内有200x200 char数组
Map ParcelMap;//同上

Robot robot[robot_num];
Berth berth[berth_num];
Boat boat[boat_num];

LinkParcel LinkParcels;
LinkParcel LockedParcels;

LinkList paths_robot[robot_num];


int money, boat_capacity, frame;
// char ch[N][N];//地图 
//int gds[N][N];

void Init()
{
		for(int i = 1; i <= n; i ++)
				scanf("%s", map.data[i] + 1);
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
		InitRobot(robot,robot_num);
		InitBerth(berth,berth_num);
		InitRoat(boat,boat_num);
		InitParcel(&ParcelMap, &LinkParcels, &LockedParcels);
		controlBoat(boat,boat_num,berth,berth_num,boat_capacity);
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
				int x, y, val;
				scanf("%d%d%d", &x, &y, &val);
				//读取到货物结构体
				ParcelMap.data[x][y] = (char)val;//强制将货物价值存为char,0表示无货物
				LinkInsertByIndex_Parcel(&LinkParcels,LinkGetLen_Parcel(&LinkParcels),*createParcel(x,y,frame,val));\
		}
		for(int i = 0; i < robot_num; i ++)
		{
				int carry,stun;//carry：0表示未携带物品；stun:0表示恢复状态(晕眩)
				scanf("%d%d%d%d", &carry, &robot[i].pos.x, &robot[i].pos.y, &stun);
				(carry, stun , &robot[i]);//机器人状态处理函数
				
		}
		for(int i = 0; i < 5; i ++)
		{
			int backstatus,aimId;//判决器返回状态,目标泊口
			scanf("%d%d\n", &backstatus, &aimId);
			boatStatusupdate(backstatus,aimId,&boat[i]);//船状态处理函数
		}
		char okk[100];
		scanf("%s", okk);
		return frame;
}

int main()
{
		Init();
		for(int zhen = 1; zhen <= 15000; zhen ++)
		{
				int frame = Input();//返回当前帧数
				for(int i = 0; i < robot_num; i ++)//机器人控制
				{
					switch (robot[i].current_status)
					{
					case IDLE:
						robotGetGoodsPrint(&robot[i],i);
						robot[i].next_status = GETTING;
						break;
					case GETTING:
						robotGetGoodsPrint(&robot[i],i);
						break;
					case SENDING:
						robotSendGoodsPrint(&robot[i],i);
						break;
					default:break;
					}
					robot[i].current_status = robot[i].next_status;
				}
				controlBoat(boat,boat_num,berth,berth_num,boat_capacity);//对船进行操作
				//消失货物列表维护
				if(frame>1000)ParcelTimedDelete(&LockedParcels,frame);
				puts("OK");
				fflush(stdout);
		}

		return 0;
}

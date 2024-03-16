#include <stdio.h>
#include <random>

#include "list.h"
#include "moveControl.h"
#include "astar.h"

#include "struct_Map.h"
#include "struct_Robot.h"
#include "struct_Berth.h"
#include "struct_Boat.h"

const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int boat_num = 5;
const int N = 200;



// struct Robot
// {
//     int x, y, goods;
//     int status;
//     int mbx, mby;
// }robot[robot_num];
// struct Berth
// {
		// int x;
		// int y;
		// int transport_time;
		// int loading_speed;
// }berth[berth_num];
// struct Boat
// {
//     int num, pos, status;
// }boat[boat_num];

Map map;
Robot robot[robot_num];
Berth berth[berth_num];
Boat boat[boat_num];
LinkList paths_robot[robot_num];

int money, boat_capacity, id;
// char ch[N][N];//地图 
int gds[N][N];
void Init()
{
		for(int i = 1; i <= n; i ++)
				scanf("%s", map.data[i] + 1);
		for(int i = 0; i < berth_num; i ++)
		{
				int id;
				scanf("%d", &id);
				scanf("%d%d%d%d", &berth[id].x, &berth[id].y, &berth[id].transport_time, &berth[id].loading_speed);
		}
		scanf("%d", &boat_capacity);
		char okk[100];
		scanf("%s", okk);
		printf("OK\n");
		fflush(stdout);
}

void robotStateInit(){
	for(int i=0;i<robot_num;i++){
		//aStarSearch(&map,robot[i].)
	}
}

int Input()
{
		scanf("%d%d", &id, &money);
		int num;//新增货物数量
		scanf("%d", &num);
		for(int i = 1; i <= num; i ++)
		{
				int x, y, val;
				scanf("%d%d%d", &x, &y, &val);
		}
		for(int i = 0; i < robot_num; i ++)
		{
				int sts;
				scanf("%d%d%d%d", &robot[i].goods, &robot[i].x, &robot[i].y, &sts);
		}
		for(int i = 0; i < 5; i ++)
				scanf("%d%d\n", &boat[i].status, &boat[i].pos);
		char okk[100];
		scanf("%s", okk);
		return id;
}

int main()
{
		Init();
		for(int zhen = 1; zhen <= 15000; zhen ++)
		{
				int id = Input();
				for(int i = 0; i < robot_num; i ++)//机器人控制
				{
					if(robot->status == ROBOT_STUCK){continue;}//机器人如果受困直接跳过
					aStarSearch(&map,);
					moveRobot(&robot[i],&paths_robot[i]);//更新机器人行进方向
					printf("move %d %d\n", i, robot[i].direct);//输出到控制台
				}
				puts("OK");
				fflush(stdout);
		}
		return 0;
}



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


int money, boat_capacity, frame;
// char ch[N][N];//地图 
int gds[N][N];

void robotStateInit();

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
		printf("OK\n");//初始化结束
		fflush(stdout);
}



int Input()
{
		scanf("%d%d", &frame, &money);//帧数和当前金额
		int increase_goods;//新增货物数量
		scanf("%d", &increase_goods);//???
		for(int i = 1; i <= increase_goods; i ++)
		{
				int x, y, val;
				scanf("%d%d%d", &x, &y, &val);//???读取到货物结构体
		}
		for(int i = 0; i < robot_num; i ++)
		{
            int carry,stun;//carry：0表示未携带物品；stun:0表示恢复状态(晕眩)
				scanf("%d%d%d%d", &carry, &robot[i].pos.x, &robot[i].pos.y, &stun);
                robotstatusupdate(carry, stun , robot[i]);//???机器人状态处理函数void robotstatusupdate(int carry,int stun ,Robot *robot)
                
		}
		for(int i = 0; i < 5; i ++)
				scanf("%d%d\n", &boat[i].status, &boat[i].aimId);
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
					//写在stuct_Robot和ROBOT里面
                    if(robot->status == ROBOT_STUCK){continue;}//机器人如果受困直接跳过

					//aStarSearch(&map,);//???函数，查找并跟新机器人目标方向
					moveRobot(&robot[i],&paths_robot[i]);//更新机器人行进方向
					printf("move %d %d\n", i, robot[i].direct);//输出到控制台
                    if(){//即将到达
                        printf("get %d %d\n", i, robot[i].direct);//???
				     }


				puts("OK");
				fflush(stdout);
		}
		return 0;
}



void robotStateInit(){//机器人状态
	for(int i=0;i<robot_num;i++){
		//aStarSearch(&map,robot[i].)
	}
}
#ifndef ROBOT_H//预定义避免重复引入
#define ROBOT_H

#include "struct_Robot.h"
#include "struct_Berth.h"
#include "astar.h"
#include "moveControl.h"

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

#define PATH_FACTOR     80
#define LOADING_FACTOR  15
#define TRANS_FACTOR    5

void robotstatusupdate(int carry,int stun ,Robot *robot);//机器人状态处理函数

LinkList* findPathToGoods(Robot rob);
LinkList* findPathToBerth(Berth* berths, Robot rob);
int* pathToDirection(LinkList* path);
int isGoodsGrid(Point pos);

//下方为实际机器人进行动作的函数

void robotsGetGoodsPrint(Robot rob[], int num);
void robotGetGoodsPrint(Robot *pRob, int id);
void robotsSendGoodsPrint(Robot rob[], int num);
void robotSendGoodsPrint(Robot *pRob, int id);

#endif
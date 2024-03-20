#ifndef ROBOT_H//预定义避免重复引入
#define ROBOT_H

#include "struct_Robot.h"
#include "struct_Berth.h"
#include "astar.h"
#include "moveControl.h"
#include "LinkParcel.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "LinkPath.h"
#include "LinkGrid.h"

#define PATH_FACTOR     80
#define LOADING_FACTOR  15
#define TRANS_FACTOR    5

void robotstatusupdate(int carry,int awake ,Robot *robot);//机器人状态处理函数

LinkPath* findPathToGoods(Robot rob, Map MapOfParcels, Grid **gridmap);
LinkPath* findPathToBerth(Berth *berths,  Robot rob, Grid **girdmap);
//int* pathToDirection(LinkList* path);
int isParcelGrid(Parcel pos);
//下方为实际机器人进行动作的函数

void robotsGetGoodsPrint(Robot rob[], int num, Grid **gridmap);
void robotGetGoodsPrint(Robot *pRob, int id, Grid **gridmap);
void robotsSendGoodsPrint(Robot rob[], int num, Grid **gridmap);
void robotSendGoodsPrint(Robot *pRob, int id, Grid **gridmap);

#endif
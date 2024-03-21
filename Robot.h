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

void robotUpdate_sysInput(int carry,int awake ,Robot *robot);//机器人状态处理函数

LinkPath* findPathToGoods(Map MapOfParcels, Robot* rob);
LinkPath* findPathToBerth(Berth *berths, Robot* rob);
//int* pathToDirection(LinkList* path);
int isParcelGrid(Parcel pos);
//下方为实际机器人进行动作的函数

// void robotGetGoodsPrint(Robot *pRob, int id);
// void robotSendGoodsPrint(Robot *pRob, int id);

void robotGetParcelPath(Robot* pRob);
void robotGetBerthPath(Robot* pRob);
void robotUpdate_Action(Robot *pRob);
void robotAction(Robot* pRob);

#endif
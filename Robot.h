#ifndef ROBOT_H//预定义避免重复引入
#define ROBOT_H

#include <stdio.h>
#include <stdlib.h>

#include "struct_Robot.h"
#include "struct_Berth.h"

#include "LinkGrid.h"
#include "LinkPath.h"
#include "LinkParcel.h"

#include "moveControl.h"
#include "astar.h"
#include "Boat.h"

void robotUpdate_sysInput(int carry,int awake ,Robot *robot);//机器人状态处理函数

LinkPath* findPathToGoods(Robot* rob);
LinkPath* findPathToBerth(Berth *berths, Robot* rob);
//int* pathToDirection(LinkList* path);
//int isParcelGrid(Parcel pos);
//下方为实际机器人进行动作的函数
void judgeCoincidentGrids(Robot* rob, LinkPath *robotpaths);
// void robotGetGoodsPrint(Robot *pRob, int id);
// void robotSendGoodsPrint(Robot *pRob, int id);

int AvoidPossibleCollide(Robot rob);

void robotGetParcelPath(Robot* pRob);
void robotGetBerthPath(Robot* pRob);
void robotUpdate_Action(Robot *pRob);
void robotAction(Robot* pRob);

#endif
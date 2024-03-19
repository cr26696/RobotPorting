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

#include "list.h"

#define PATH_FACTOR     80
#define LOADING_FACTOR  15
#define TRANS_FACTOR    5

void robotstatusupdate(int carry,int stun ,Robot *robot);//机器人状态处理函数

LinkList* findPathToGoods(Robot rob, Map MapOfParcels);
LinkList* findPathToBerth(Berth* berths, Robot rob);
int* pathToDirection(LinkList* path);
<<<<<<< HEAD
int isParcelsGrid(Parcel pos);
=======
int isParcelGrid(Parcel pos);
>>>>>>> 755aea08930819d403bd766d1cc2ca0a4fbeb8a2

//下方为实际机器人进行动作的函数

void robotsGetGoodsPrint(Robot rob[], int num);
void robotGetGoodsPrint(Robot *pRob, int id);
void robotsSendGoodsPrint(Robot rob[], int num);
void robotSendGoodsPrint(Robot *pRob, int id);

#endif
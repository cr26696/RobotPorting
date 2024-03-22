#ifndef INITALL_H//预定义避免重复引入
#define INITALL_H

#include <stdio.h>
#include <stdlib.h>

#include "struct_Robot.h"
#include "struct_Berth.h"
#include "struct_Boat.h"
#include "struct_Map.h"
#include "struct_Grid.h"

#include "astar.h"
#include "Boat.h"
#include "LinkParcel.h"

/*
初始化顺序 船-地图-泊口->机器人 即机器人必须在泊口后
*/
void InitBerth(Berth berths[],int berth_num);
void InitBoat(Boat boats[],int boatCount);
void InitRobot(Map map,Grid** gridMap, Berth berths[],int berthCount,Robot robots[],int robotCount);//机器人状态初始化???判断是否受困
void InitParcel(Map *ParcelMap, LinkParcel *pLinkParcel, LinkParcel *pLockedParcels);

#endif
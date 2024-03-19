#include <stdio.h>
#include <stdlib.h>

#include "struct_Robot.h"
#include "struct_Berth.h"
#include "struct_Boat.h"
#include "struct_Map.h"

#include "LinkParcel.h"
/*
初始化顺序 船-地图-泊口->机器人 即机器人必须在泊口后
*/
void InitBerth(Berth berths[],int berth_num);
void InitBoat(Boat boats[],int boatCount);
void InitRobot(Map map,Berth berth[],int berthCount,Robot robots[],int robotCount);
void InitParcel(Map *ParcelMap, LinkParcel *pLinkParcel, LinkParcel *pLockedParcels);


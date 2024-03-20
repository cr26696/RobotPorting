#ifndef BOAT_H//预定义避免重复引入
#define BOAT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "struct_Boat.h"
#include "struct_Berth.h"

void boatStatusupdate(int backstatu,int aimId,Boat *boat);//更新船的状态
void controlBoat(Boat boat[],int boat_num,Berth berth[],int berth_num,int boat_capacity);
float evaluateBerth(int loadSpeed,float friscoe,int transportTime,float secocoe,int pathLength ,float thricoe);
void countgoodsnum(Berth *berth,Boat *boat);//计算泊口的货物数量和船上的货物数量
void AllboatatVIRTUAL(Boat *boat,int boat_num,Berth berth[],int berth_num);
#endif
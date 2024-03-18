#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "struct_Robot.h"
#include "struct_Berth.h"
#include "struct_Boat.h"
#include "struct_Map.h"

#include "LinkParcel.h"

void Inittotal(Robot robot[],int robot_num,Boat boat[],int boat_num,Berth berth[],int berth_num,int boat_capacity );
void InitRobot(Robot robot[],int robot_num);
void InitBerth(Berth berth[],int berth_num);
void InitRoat(Boat boat[],int boat_num);
void InitParcel(Map *ParcelMap, LinkParcel *linkParcel);


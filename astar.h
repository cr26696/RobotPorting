#ifndef ASTAR_H//预定义避免重复引入
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geometry.h" 
#include "struct_Map.h"
#include "LinkGrid.h" 
#include "LinkPath.h"

int isValidGrid(Map *map, Point point);//返回1表示空地
//LinkPath* aStarSearch(Map *map, Grid** gridMap, Point Psrc, Point Pdest);//返回一个path
LinkPath* aStarSearch(Map *map, /*Grid** gridMap,*/ Point Psrc, Point Pdest);

LinkPath* generatePath(Grid *temp);//传入current的拷贝

#endif
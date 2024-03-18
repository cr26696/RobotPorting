#ifndef ASTAR_H//预定义避免重复引入
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h" 
#include "geometry.h" 
#include "struct_Map.h"

int isValidGrid(Map *map, Point point);//返回1表示空地
LinkList* aStarSearch( struct Map *map, Point Psrc, Point Pdest);//返回一个path

LinkList* generatePath(Grid temp);//传入current的拷贝

#endif
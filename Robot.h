#ifndef ROBOT_H//预定义避免重复引入
#define ROBOT_H

#include "struct_Robot.h"
#include "astar.h"

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>


int isGoodsGrid(Map *goodsmap, Point pos);
LinkList* searchGoods(Map *goodsmap, Robot rob);
int* pathToDirection(LinkList* path);
int* pathToDirection(LinkList* path);

#endif
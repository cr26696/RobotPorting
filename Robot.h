#ifndef ROBOT_H//预定义避免重复引入
#define ROBOT_H

#include "struct_Robot.h"
#include "struct_Berth.h"
#include "astar.h"

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

#define PATH_FACTOR     80
#define LOADING_FACTOR  15
#define TRANS_FACTOR    5

int isGoodsGrid(Map *goodsmap, Point pos);
LinkList* searchGoods(Map *goodsmap, Robot rob);
int* pathToDirection(LinkList* path);
int* pathToDirection(LinkList* path);

#endif
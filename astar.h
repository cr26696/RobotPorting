#ifndef ASTAR_H//预定义避免重复引入
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>

int isValueGrid(int x,int y);//
void aStarSearch(Grid src, Grid dest);//返回一个path
void getFdistance(Grid *grid, Goods *goods);//计算F通过指针传入grid

#endif
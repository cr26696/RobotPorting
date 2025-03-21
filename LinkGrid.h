#ifndef LINKGRID_H//预定义避免重复引入
#define LINKGRID_H

#include <stdio.h>
#include <stdlib.h>


#include "geometry.h"
#include "struct_Grid.h"

//链表节点，存储类型为Grid
typedef struct LinkGrid
{
    Grid *grid; //格子数据类型
    struct LinkGrid *next; //下一个链表节点的地址
} LinkGrid;

LinkGrid *LinkInit_Grid(LinkGrid *L);
LinkGrid *LinkCreate_Grid(int len);
void LinkDelete_Grid(LinkGrid *L);
void LinkSoftDelete_Grid(LinkGrid *L);
//void LinkInsert_Head_Grid(LinkGrid *L, Parcel parcel);

int LinkInsert_ByIndex_Grid(LinkGrid *L, int pos, Grid* grid);
int LinkDelete_ByIndex_Grid(LinkGrid *L, int pos);
int LinkDelete_ByPoint_Grid(LinkGrid *L, Point point);
int LinkDelete_ByObj_Grid(LinkGrid *L, Grid* grid);
int LinkSoftDelete_ByObj_Grid(LinkGrid *L, Grid* grid);
// int LinkDelete_Save_Grid(LinkGrid *L, int pos, Grid* grid);
int LinksearchPos_ByObj_Grid(LinkGrid *L, Grid* grid);//???
Grid* LinksearchObj_ByPos_Grid(LinkGrid *L, int pos);//???
LinkGrid *LinksearchLink_ByObj_Grid(LinkGrid *L, Grid* grid);//查找其实是按grid的xy匹配查找的，返回位置链头，否则返回NULL
void LinkReverse_Grid(LinkGrid *L);//444
int LinkIsEmpty_Grid(LinkGrid *L);//222

int LinkGetLen_Grid(LinkGrid* L);
LinkGrid* ListsearchMin_Grid(LinkGrid *L);
Grid* ListgetMinCostGrid_Grid(LinkGrid *L);

#endif
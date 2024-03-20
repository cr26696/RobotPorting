#ifndef LIST_GRID_H//预定义避免重复引入
#define LIST_GRID_H

#include <stdio.h>
#include <stdlib.h>


#include "geometry.h"

//链表节点，存储类型为Grid
typedef struct LinkGrid
{
    Grid *grid; //格子数据类型
    struct LinkGrid *next; //下一个链表节点的地址
} LinkGrid;



LinkGrid *initList(LinkGrid *L);
LinkGrid *createList(int len);
// void insertLinkListHead(LinkList *L, Grid grid);

int insertLinkList(LinkGrid *L, int pos, Grid grid);
int deleteLinkList(LinkGrid *L, int pos);
int deletLinkListByPoint(LinkGrid *L, Point point);
int deletLinkListByGrid(LinkGrid *L, Grid grid);
int deleteLinkListSave(LinkGrid *L, int pos, Grid *grid);
void reverseLinkList(LinkGrid *L);
LinkGrid *searchLinkList(LinkGrid *L, Grid grid);//查找其实是按grid的xy匹配查找的，返回位置链头，否则返回NULL
int getLen(LinkGrid *L);
int isEmpty(LinkGrid *L);
void deleteLink_Grid(LinkGrid *L);
void printLinkList(LinkGrid *L);
LinkGrid* searchMinList(LinkGrid *L);//返回F最小(相同时G最小)的节点 返回链表
Grid* getMinCostGrid(LinkGrid *L);
#endif
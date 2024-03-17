#ifndef LIST_H//预定义避免重复引入
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "geometry.h"

// typedef struct 
// {   
//     int x,y;
//     int value;
//     int isLocked;
// }Goods;

//链表存储类型为Grid
typedef struct Node
{
    Grid grid; //格子数据类型
    struct LinkList *next; //下一个链表节点的地址
} LinkList;

LinkList *initList(LinkList *L);
LinkList *createList(int len);
void insertLinkListHead(LinkList *L, Grid grid);
int insertLinkList(LinkList *L, int pos, Grid grid);
int deleteLinkList(LinkList *L, int pos);
int deleteLinkListSave(LinkList *L, int pos, Grid *grid);
void reverseLinkList(LinkList *L);
LinkList *searchLinkList(LinkList *L, Grid grid);//查找其实是按grid的xy匹配查找的，返回位置链头，否则返回NULL
int getLen(LinkList *L);
int isEmpty(LinkList *L);
void printLinkList(LinkList *L);
LinkList* searchMinList(LinkList *L);//返回F最小(相同时G最小)的节点 返回链表
int deletLinkByXY(LinkList *L, Grid grid);

#endif
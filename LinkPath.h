#ifndef LINKPATH_H//预定义避免重复引入
#define LINKPATH_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "geometry.h"

//链表节点，存储类型为Parcel
typedef struct LinkPath
{
    Point pos; //货物数据类型
    struct LinkPath *next; //下一个链表节点的地址
} LinkPath;

LinkPath *initList_Path(LinkPath *L);
int insertListPath(LinkPath *L, int pos, Point point);
void linkDelete_Path(LinkPath *L);
int deletListPathByPoint(LinkPath *L, Point point);
void reverseListPath(LinkPath *L);
LinkPath *searchListPath(LinkPath *L, Point point);
int LinkGetLen_Path(LinkPath *L);
int isEmpty(LinkPath *L);
void freeWholeListPath(LinkPath *L);
void printLinkList(LinkPath *L);
int deleteListPath(LinkPath *L, int pos);

int LinkInsertEnd_Path(LinkPath *endNode, Point point);//输入尾链表，在其后新建并插入点 返回值1成功0失败

#endif


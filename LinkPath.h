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

LinkPath* linkInit_Path(LinkPath *L);
int linkInsert_byIndex_Path(LinkPath *L, int pos, Point point);
void linkDelete_Path(LinkPath *L);
int linkDelete_byObj_Path(LinkPath *L, Point point);
int linkDelete_byPos_Path(LinkPath *L, int pos);
void linkReverse_Path(LinkPath *L);
LinkPath *linkSearch_byPos_Path(LinkPath *L, Point point);
int linkGetLen_Path(LinkPath *L);
int linkIsEmpty_Path(LinkPath *L);
int linkHasObj_Path(LinkPath *L,Point point);
// void linkfreeWhole_Path(LinkPath *L);

#endif


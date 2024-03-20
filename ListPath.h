#ifndef LISTPATH_H//预定义避免重复引入
#define LISTPATH_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "geometry.h"

//链表节点，存储类型为Parcel
typedef struct ListPath
{
    Point pos; //货物数据类型
    struct LinkParcel *next; //下一个链表节点的地址
} ListPath;

ListPath *initList(ListPath *L);
int insertListPath(ListPath *L, int pos, Point point);
int deleteListPath(ListPath *L, int pos);
int deletListPathByPoint(ListPath *L, Point point);
void reverseListPath(ListPath *L);
ListPath *searchListPath(ListPath *L, Point point);
int getLen(ListPath *L);
int isEmpty(ListPath *L);
void freeWholeListPath(ListPath *L);
void printLinkList(ListPath *L);

int LinkInsertEnd_Path(ListPath *endNode, Point point);//输入尾链表，在其后新建并插入点 返回值1成功0失败

#endif


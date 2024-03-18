#ifndef LINKPARCEL_H//预定义避免重复引入
#define LINKPARCEL_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "struct_Parcel.h"

//链表节点，存储类型为Parcel
typedef struct LinkParcel
{
    Parcel parcel; //货物数据类型
    struct LinkParcel *next; //下一个链表节点的地址
} LinkParcel;

LinkParcel *initList(LinkParcel *L);
LinkParcel *createList(int len);
void insertLinkListHead(LinkParcel *L, Parcel parcel);
int insertLinkList(LinkParcel *L, int pos, Parcel parcel);
int deleteLinkList(LinkParcel *L, int pos);
int deletLinkListByPoint(LinkParcel *L, Point point);
int deletLinkListByParcel(LinkParcel *L, Parcel parcel);
int deleteLinkListSave(LinkParcel *L, int pos, Parcel *parcel);
void reverseLinkList(LinkParcel *L);
LinkParcel *searchLinkList(LinkParcel *L, Parcel parcel);//查找其实是按grid的xy匹配查找的，返回位置链头，否则返回NULL
int getLen(LinkParcel *L);
int isEmpty(LinkParcel *L);
#endif

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

LinkParcel *LinkInit_Parcel(LinkParcel *L);
LinkParcel *LinkCreate_Parcel(int len);
//void LinkInsert_Head_Parcel(LinkParcel *L, Parcel parcel);
int LinkInsert_ByIndex_Parcel(LinkParcel *L, int pos, Parcel parcel);
int LinkDelete_ByIndex_Parcel(LinkParcel *L, int pos);
int LinkDelete_ByPoint_Parcel(LinkParcel *L, Point point);
int LinkDelete_ByObj_Parcel(LinkParcel *L, Parcel parcel);
int LinkDelete_Save_Parcel(LinkParcel *L, int pos, Parcel *parcel);
int LinksearchPos_ByObj_Parcel(LinkParcel *L, Parcel parcel);
Parcel LinksearchObj_ByPos_Parcel(LinkParcel *L, int pos);
LinkParcel *LinksearchLink_ByObj_Parcel(LinkParcel *L, Parcel parcel);//查找其实是按grid的xy匹配查找的，返回位置链头，否则返回NULL
void LinkReverse_Parcel(LinkParcel *L);
int LinkGetLen_Parcel(LinkParcel *L);
int LinkIsEmpty_Parcel(LinkParcel *L);
Parcel LinksearchParcelByPos(LinkParcel *L, int pos);


Parcel createParcel(int x,int y, int time, int value);
void ParcelTimedDelete(LinkParcel *Link,int frame);
#endif

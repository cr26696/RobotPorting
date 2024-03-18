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
void LinkInsertHead_Parcel(LinkParcel *L, Parcel parcel);
int LinkInsertByIndex_Parcel(LinkParcel *L, int pos, Parcel parcel);
int LinkDeleteByIndex_Parcel(LinkParcel *L, int pos);
int LinkDeleteByPoint_Parcel(LinkParcel *L, Point point);
int LinkDeleteByObj_Parcel(LinkParcel *L, Parcel parcel);
int LinkDeleteSave_Parcel(LinkParcel *L, int pos, Parcel *parcel);
LinkParcel *LinksearchByObj_Parcel(LinkParcel *L, Parcel parcel);//查找其实是按grid的xy匹配查找的，返回位置链头，否则返回NULL
int LinksearchPosByObj_Parcel(LinkParcel *L, Parcel parcel);
void LinkReverse_Parcel(LinkParcel *L);
int LinkGetLen_Parcel(LinkParcel *L);
int LinkIsEmpty_Parcel(LinkParcel *L);
#endif

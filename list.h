#ifndef LIST_H//预定义避免重复引入
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Grid {
    int x,y;
    Grid* father;
    int G, F, H;
    int inOpen,inClose;
    int typeOfgrid;//格子类型？
}Grid;

typedef struct 
{   
    int x,y;
    int value;
    int isLocked;
}Goods;

typedef struct Node
{
    Grid grid; //格子
    struct Node *next; //指针域
} LinkList;

LinkList *initList(LinkList *L);
LinkList *createList(int len);
int insertLinkList(LinkList *L, int pos, Grid *grid);
int deleteLinkList(LinkList *L, int pos, Grid *grid);
void reverseLinkList(LinkList *L);
LinkList *seachLinkList(LinkList *L, Grid grid);
int getLen(LinkList *L);
int isEmpty(LinkList *L);
void printLinkList(LinkList *L);

#endif
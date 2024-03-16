#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// typedef struct Grid {
//     int x,y;
//     Grid* father;
//     int G, F, H;
//     int inOpen,inClose;
//     int typeOfgrid;//格子类型？
// }Grid;

// typedef struct 
// {   
//     int x,y;
//     int value;
//     int isLocked;
// }Goods;

// typedef struct Node
// {
//     Grid grid; //格子
//     struct Node *next; //指针域
// } LinkList;

//初始化，创建头结点
LinkList *initList(LinkList *L)
{
    L = (LinkList *) malloc(sizeof(LinkList));//为头结点分配空间
    L->next = NULL;//头结点指针域置空
    return L;
}

//创建指定个数的单链表
LinkList *createList(int len)
{
    int i;
    int x,y;
    LinkList *L = initList(L), *r, *n;//分别定义头指针、尾指针、新指针
    r = L;//尾指针初始化为头指针
    for(i = 0;i < len;i ++)
    {   
        scanf("%d %d", &x, &y);
        n = (LinkList *) malloc(sizeof(LinkList));//申请空间
        n->grid.loc.x = x;
        n->grid.loc.y = y;
        n->next = NULL;//新指针指针域置空
        r->next = n;//将新指针链入单链表末尾
        r = r->next;//尾指针往后移
    }
    return L;
}


//将元素插入头部
// int insertLinkList(LinkList *L, Grid grid)
// {
//     LinkList *r = L, *n;
//     n = (LinkList *) malloc(sizeof(LinkList));
//     n->grid = grid;
//     n->next = L;
//     while(--pos > 0)
//     {
//         r = r->next;//将尾指针移动到插入位置
//     }
//     n->next = r->next;//先把新指针（插入值）链入尾指针后一个节点
//     r->next = n;//再把新指针（插入值）链入尾指针之后
//     return 1;
// }
//将元素插入指定位置
int insertLinkList(LinkList *L, int pos, Grid grid)
{
    if(pos < 1 || pos > getLen(L)+1) return 0;//插入位置错误
    LinkList *r = L, *n;
    n = (LinkList *) malloc(sizeof(LinkList));
    n->grid = grid;
    n->next = NULL;
    while(--pos > 0)
    {
        r = r->next;//将尾指针移动到插入位置
    }
    n->next = r->next;//先把新指针（插入值）链入尾指针后一个节点
    r->next = n;//再把新指针（插入值）链入尾指针之后
    return 1;
}
//将指定位置元素删除,成功返回1,错误返回0
int deleteLinkList(LinkList *L, int pos)
{
    if(pos < 1 || pos > getLen(L)) return 0;//删除位置错误
    LinkList *r = L, *d;
    while(--pos > 0)
    {
        r = r->next;//将尾指针移动到删除位置
    }
    d = r->next;//删除元素节点
    r->next = d->next;//将尾指针跳过删除节点链入下一个节点
    free(d);//释放删除节点
    return 1;
}
int deletLinkByXY(LinkList *L, Grid grid){
    LinkList *r = L, *d, *temp;
    while(r->grid.loc.x != grid.loc.x && r->grid.loc.y != grid.loc.y){
        r = r->next;
    }
    d = r->next;
    r->next = d->next;
    free(d);
    return 1;
}
int deleteLinkListSave(LinkList *L, int pos, Grid *grid)
{
    if(pos < 1 || pos > getLen(L)) return 0;//删除位置错误
    LinkList *r = L, *d;
    while(--pos > 0)
    {
        r = r->next;//将尾指针移动到删除位置
    }
    d = r->next;//删除元素节点
    *grid = d->grid;//保存删除元素值
    r->next = d->next;//将尾指针跳过删除节点链入下一个节点
    free(d);//释放删除节点
    return 1;
}
//转置单链表：采用头插法
void reverseLinkList(LinkList *L)
{
    LinkList *r, *p, *q;//定义尾指针（紧贴头指针）、欲插入指针、遍历指针
    r = L->next;//尾指针紧贴头指针
    p = q = r->next;//从第二个元素开始
    r->next = NULL;//尾指针置空
    while(q)//q相当于q != NULL
    {
        q = q->next;//遍历指针后移
        p->next = r;//欲插入指针链入尾指针之前
        L->next = p;//欲插入指针链入头指针之后
        r = p;//尾指针向前移
        p = q;//欲插入指针与遍历指针同步
    }
}
//查找其实是按grid的xy匹配查找的，返回位置链头，否则返回NULL
LinkList *searchLinkList(LinkList *L, Grid grid)
{
    if(isEmpty(L)) return NULL;
    int pos = 1;//位序从1开始、下标从零开始
    LinkList *r = L->next;
    while(r)
    {
        if(r->grid.loc.x == grid.loc.x && r->grid.loc.y == grid.loc.y) return r;//找到指定元素，返回位序
        r = r->next;//尾指针后移
        pos ++;
    }
    return NULL;
}
int searchLinkListPos(LinkList *L, Grid grid)
{
    if(isEmpty(L)) return -1;
    int pos = 1;//位序从1开始、下标从零开始
    LinkList *r = L->next;
    while(r)
    {
        if(r->grid.loc.x == grid.loc.x && r->grid.loc.y == grid.loc.y) return pos;//找到指定元素，链表头
        r = r->next;//尾指针后移
        pos ++;
    }
    return -1;
}

int getLen(LinkList *L)
{
    if(L->next == NULL) return 0;//头指针指针域为空，说明单链表不含任何元素
    int len = 0;
    LinkList *r = L->next;
    while(r)
    {
        r = r->next;//尾指针后移
        len++;
    }
    return len;
}

int isEmpty(LinkList *L)
{
    return !L->next;//L->next == NULL亦可
}

void printLinkList(LinkList *L)
{
    LinkList *p;
    p = L->next;
    while(p)
    {
        printf("[%d %d]\n\r",p->grid.loc.x, p->grid.loc.y);
        p = p->next;
    }
}

LinkList* searchMinList(LinkList *L){
    LinkList *r = L, *minnode = NULL;//
    int currentminF = r->grid.F;
    int currentminG = r->grid.G;
    while(r->next != NULL){
        if((r->grid.F < currentminF) || (r->grid.F == currentminF && r->grid.G < currentminG)){
            currentminF = r->grid.F;
            currentminG = r->grid.G;
            minnode = r;
        }
        else if(r->grid.F == currentminF && r->grid.G == currentminG){
            LinkList *newnode;
            newnode->grid = r->grid;
            if(minnode == NULL){
                minnode = newnode;
            }
            else{
                LinkList *temp = minnode;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = newnode;
            }
        }
        r = r->next;
    }
    return minnode;
}
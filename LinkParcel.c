#include "LinkParcel.h"

//分配内存，链表创建头结点
LinkParcel *initList(LinkParcel *L)
{
    L = (LinkParcel *) malloc(sizeof(LinkParcel));//为头结点分配空间
    L->next = NULL;//头结点指针域置空
    return L;
}

//创建指定个数的单链表
LinkParcel *createList(int len)
{
    int i;
    int x,y;
    LinkParcel *L = initList(L), *r, *n;//分别定义头指针、尾指针、新指针
    r = L;//尾指针初始化为头指针
    for(i = 0;i < len;i ++)
    {   
        scanf("%d %d", &x, &y);
        n = (LinkParcel *) malloc(sizeof(LinkParcel));//申请空间
        n->parcel.loc.x = x;
        n->parcel.loc.y = y;
        n->next = NULL;//新指针指针域置空
        r->next = n;//将新指针链入单链表末尾
        r = r->next;//尾指针往后移
    }
    return L;
}


// //输入链表头，货物的拷贝，在对应链表头插入货物 暂时不要用
// void insertLinkListHead(LinkParcel *L, Parcel parcel)
// {
//     LinkParcel *N;//新节点 地址指针
//     N = (LinkParcel *) malloc(sizeof(LinkParcel));//N请求一片空内存区域
//     N->parcel = parcel;
//     N->next = L;//新增货物数据存于N，next指向原链表头
//     L = N;//L存储新的链表头地址
//     //N T在函数调用结束即被释放。
//     return;
// }

//输入表头，位置，货物拷贝，插入位置后并返回1成功 0失败
int insertLinkList(LinkParcel *L, int pos, Parcel parcel)
{
    if(pos < 1 || pos > getLen(L)+1) return 0;//插入位置错误
    LinkParcel *r = L, *n;
    n = (LinkParcel *) malloc(sizeof(LinkParcel));
    n->parcel = parcel;
    n->next = NULL;
    while(--pos > 0)
    {
        r = r->next;//将尾指针移动到插入位置
    }
    n->next = r->next;//先把新指针（插入值）链入尾指针后一个节点
    r->next = n;//再把新指针（插入值）链入尾指针之后
    return 1;
}
//删除指定位置处链表元素,成功返回1,错误返回0
int deleteLinkList(LinkParcel *L, int pos)
{
    if(pos < 1 || pos > getLen(L)) return 0;//删除位置错误
    LinkParcel *r = L, *d;
    while(--pos > 0)
    {
        r = r->next;//将尾指针移动到删除位置
    }
    d = r->next;//删除元素节点
    r->next = d->next;//将尾指针跳过删除节点链入下一个节点
    free(d);//释放删除节点
    return 1;
}
//输入Point将对应位置链表元素删除,成功返回1,错误返回0
int deletLinkListByPoint(LinkParcel *L, Point point){
    LinkParcel *r = L, *d;
    do{
        if(r->parcel.loc.x == point.x && r->parcel.loc.y == point.y){
            d = r;//r坐标位置完全对应
            r->next = d->next;
            free(d);
            return 1;//找到，跳出循环
        }
    }while(r->next);
    return 0;
}
int deletLinkListByparcel(LinkParcel *L, Parcel parcel){
    LinkParcel *r = L, *d;
    do{
        if(r->parcel.loc.x == parcel.loc.x && r->parcel.loc.y == parcel.loc.y){
            d = r;//r坐标位置完全对应
            r->next = d->next;
            free(d);
            return 1;//找到，跳出循环
        }
    }while(r->next);
    return 0;
}
int deleteLinkListSave(LinkParcel *L, int pos, Parcel *parcel)
{
    if(pos < 1 || pos > getLen(L)) return 0;//删除位置错误
    LinkParcel *r = L, *d;
    while(--pos > 0)
    {
        r = r->next;//将尾指针移动到删除位置
    }
    d = r->next;//删除元素节点
    *parcel = d->parcel;//保存删除元素值
    r->next = d->next;//将尾指针跳过删除节点链入下一个节点
    free(d);//释放删除节点
    return 1;
}
//转置单链表：采用头插法
void reverseLinkList(LinkParcel *L)
{
    LinkParcel *r, *p, *q;//定义尾指针（紧贴头指针）、欲插入指针、遍历指针
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
//查找其实是按parcel的xy匹配查找的，返回位置链头，否则返回NULL
LinkParcel *searchLinkList(LinkParcel *L, Parcel parcel)
{
    if(isEmpty(L)) return NULL;
    int pos = 1;//位序从1开始、下标从零开始
    LinkParcel *r = L->next;
    while(r)
    {
        if(r->parcel.loc.x == parcel.loc.x && r->parcel.loc.y == parcel.loc.y) return r;//找到指定元素，返回位序
        r = r->next;//尾指针后移
        pos ++;
    }
    return NULL;
}
int searchLinkListPos(LinkParcel *L, Parcel parcel)
{
    if(isEmpty(L)) return -1;
    int pos = 1;//位序从1开始、下标从零开始
    LinkParcel *r = L->next;
    while(r)
    {
        if(r->parcel.loc.x == parcel.loc.x && r->parcel.loc.y == parcel.loc.y) return pos;//找到指定元素，链表头
        r = r->next;//尾指针后移
        pos ++;
    }
    return -1;
}
//返回尾部链表长度
int getLen(LinkParcel *L)
{
    if(L->next == NULL) return 0;//头指针指针域为空，说明单链表不含任何元素
    int len = 0;
    LinkParcel *r = L->next;
    while(r)
    {
        r = r->next;//尾指针后移
        len++;
    }
    return len;
}
//空返回1 非空返回0
int isEmpty(LinkParcel *L)
{
    return !L->next;//L->next == NULL亦可
}

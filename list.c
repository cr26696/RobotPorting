#include "list.h"

#include <malloc.h>
//分配内存，创建链表头结点,下一节点为NULL
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


// //输入链表头，格子的拷贝，在对应链表头插入格子 暂时不要用
// void insertLinkListHead(LinkList *L, Grid grid)
// {
//     LinkList *N;//新节点 地址指针
//     N = (LinkList *) malloc(sizeof(LinkList));//N请求一片空内存区域
//     N->grid = grid;
//     N->next = L;//新增格子数据存于N，next指向原链表头
//     L = N;//L存储新的链表头地址
//     //N T在函数调用结束即被释放。
//     return;
// }

//输入表头，位置，格点拷贝，插入位置后并返回1成功 0失败
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
//删除指定位置处链表元素,成功返回1,错误返回0
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
//输入Point将对应位置链表元素删除,成功返回1,错误返回0
int deletLinkListByPoint(LinkList *L, Point point){
	LinkList *r = L, *d;
	do{
		if(r->grid.loc.x == point.x && r->grid.loc.y == point.y){
			d = r;//r坐标位置完全对应
			r->next = d->next;
			free(d);
			return 1;//找到，跳出循环
		}
	}while(r->next);
	return 0;
}
int deletLinkListByGrid(LinkList *L, Grid grid){
	LinkList *r = L, *d;
	do{
		if(r->grid.loc.x == grid.loc.x && r->grid.loc.y == grid.loc.y){
			d = r;//r坐标位置完全对应
			r->next = d->next;
			free(d);
			return 1;//找到，跳出循环
		}
	}while(r->next);
	return 0;
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
//返回尾部链表长度
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
//空返回1 非空返回0
int isEmpty(LinkList *L)
{
	return !L->next;//L->next == NULL亦可
}
//清除链表每一个结点（包括头结点）
void deleteLink_Grid(LinkList *L){
	LinkList* r = L;
	LinkList* t;
	r = r->next;
	if(r!=NULL){
		do
		{
			t = r;
			r = r->next;
			free(t);
		} while (r!=NULL);
	}
	free(L);
	return;
}
//输出
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
//传入链表头
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
//传入表头，返回一个最小F，G值的Grid的地址
Grid* getMinCostGrid(LinkList *L){
	LinkList *r = L;
	Grid *grid;
	int minF,minG;
	if(r->next){//链表至少有一个格点
		r = r->next;
		grid = &r->grid;
		minF = grid->F;
		minG = grid->G;
	}
	else return NULL;//链表为空，返回NULL
	while(r->next){
		r = r->next;
		if(r->grid.F < minF){
			grid = &r->grid;
			minF = grid->F;
			minG = grid->G;
			continue;
		}else if(r->grid.F == minF){
			if(r->grid.G < minG){
				grid = &r->grid;
				minG = grid->G;
				continue;
			}
		}
		//剩余情况为大于minF
	}
	//遍历链表后，返回最小格点地址。
	return grid;
}
#include "ListPath.h"

ListPath *initList(ListPath *L){
	L = (ListPath *) malloc(sizeof(ListPath));//为头结点分配空间
	L->next = NULL;//头结点指针域置空
	return L;
}

int insertListPath(ListPath *L, int pos, Point point){
	if(pos < 1 || pos > getLen(L)+1) return 0;//插入位置错误
	ListPath *r = L, *n;
	n = (ListPath *) malloc(sizeof(ListPath));
	n->pos = point;
	n->next = NULL;
	while(--pos > 0)
	{
		r = r->next;//将尾指针移动到插入位置
	}
	n->next = r->next;//先把新指针（插入值）链入尾指针后一个节点
	r->next = n;//再把新指针（插入值）链入尾指针之后
	return 1;
}

int deleteListPath(ListPath *L, int pos){
	if(pos < 1 || pos > getLen(L)) return 0;//删除位置错误
	ListPath *r = L, *d;
	while(--pos > 0)
	{
		r = r->next;//将尾指针移动到删除位置
	}
	d = r->next;//删除元素节点
	r->next = d->next;//将尾指针跳过删除节点链入下一个节点
	free(d);//释放删除节点
	return 1;
}

int deletListPathByPoint(ListPath *L, Point point){
	ListPath *r = L, *d;
	while(r->next)//r != NULL 
		if(isSamePosition(r->pos, point)){
			d = r->next;
			r->next = d->next;
			free(d);//释放链表节点和对应的Grid
			return 1;//找到，跳出循环
		}else{
			r = r->next;
		}
	return 0;
}

void reverseListPath(ListPath *L){
	ListPath *r, *p, *q;//定义尾指针（紧贴头指针）、欲插入指针、遍历指针
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

ListPath *searchListPath(ListPath *L, Point point){//返回无头节点的链表
	if(isEmpty(L)) return NULL;
	int pos = 1;//位序从1开始、下标从零开始
	ListPath *r = L->next;
	while(r)
	{
		if(r->pos.x == point.x && r->pos.y == point.y) return r;//找到指定元素，返回位序
		r = r->next;//尾指针后移
		pos ++;
	}
	return NULL;    
}

int getLen(ListPath *L){
	if(L->next == NULL) return 0;//头指针指针域为空，说明单链表不含任何元素
	int len = 0;
	ListPath *r = L->next;
	while(r)
	{
		r = r->next;//尾指针后移
		len++;
	}
	return len;
}

int isEmpty(ListPath *L){
    return !L->next;
}

void freeWholeListPath(ListPath *L){
	ListPath* r = L;
	ListPath* t;
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

void printLinkList(ListPath *L){
	ListPath *p;
	p = L->next;
	while(p){
		printf("[%d %d]\n\r",p->pos.x, p->pos.y);
		p = p->next;
	}
}

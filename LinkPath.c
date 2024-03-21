#include "LinkPath.h"

LinkPath *linkInit_Path(LinkPath *L){
	L = (LinkPath *) malloc(sizeof(LinkPath));//为头结点分配空间
	L->next = NULL;//头结点指针域置空
	return L;
}

int linkInsert_byPos_Path(LinkPath *L, int pos, Point point){
	if(pos < 1 || pos > linkGetLen_Path(L)+1) return 0;//插入位置错误
	LinkPath *r = L, *n;
	n = (LinkPath *) malloc(sizeof(LinkPath));
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

void linkDelete_Path(LinkPath *L){
	
	LinkPath* r = L;
	LinkPath* t;
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

int linkDelete_byPoint_Path(LinkPath *L, Point point){
	LinkPath *r = L, *d;
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

//传坐标 
int linkDelete_byPos_Path(LinkPath *L, int pos){
	if(pos < 1 || pos > linkGetLen_Path(L)) return 0;//删除位置错误
	LinkPath *r = L, *d;
	while(--pos > 0)
	{
		r = r->next;//将尾指针移动到删除位置
	}
	d = r->next;//删除元素节点
	r->next = d->next;//将尾指针跳过删除节点链入下一个节点
	free(d);//释放删除节点
	return 1;
}

void linkReverse_Path(LinkPath *L){
	LinkPath *r, *p, *q;//定义尾指针（紧贴头指针）、欲插入指针、遍历指针
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

LinkPath *linkSearch_byPos_Path(LinkPath *L, Point point){//返回无头节点的链表
	if(linkIsEmpty_Path(L)) return NULL;
	int pos = 1;//位序从1开始、下标从零开始
	LinkPath *r = L->next;
	while(r)
	{
		if(r->pos.x == point.x && r->pos.y == point.y) return r;//找到指定元素，返回位序
		r = r->next;//尾指针后移
		pos ++;
	}
	return NULL;    
}

int linkGetLen_Path(LinkPath *L){
	if(L==NULL) return 0;
	if(L->next == NULL) return 0;//头指针指针域为空，说明单链表不含任何元素
	int len = 0;
	LinkPath *r = L->next;
	while(r)
	{
		r = r->next;//尾指针后移
		len++;
	}
	return len;
}

int linkIsEmpty_Path(LinkPath *L){
    return !L->next;
}

// void linkDelete_Path(LinkPath *L){
// 	LinkPath* r = L;
// 	LinkPath* t;
// 	r = r->next;
// 	if(r!=NULL){
// 		do
// 		{
// 			t = r;
// 			r = r->next;
// 			free(t);
// 		} while (r!=NULL);
// 	}
// 	free(L);
// 	return;
// }


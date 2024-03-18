#include "astar.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"

#define VALUE_INF 65535
#define NEIGHBOR_LEFT 0
#define NEIGHBOR_RIGHT 1
#define NEIGHBOR_UP 2
#define NEIGHBOR_DOWN 3

#define MOVE_COST 10
//传入地图，目标点，返回1可走 0不可走
int isValidGrid(Map *map, Point point){
  char target = map->data[point.x][point.y];
  if (target=='.' || target=='A'){return 1;}
  else{return 0;}
}
//输入地图，起止点，返回起点到终点的路径，包括起点与终点格，至少一格，不可达到为NULL
LinkList* aStarSearch(Map *map, Point Psrc, Point Pdest){
//int max_nodes = map.length * map[0].length;

  LinkList *openList = initList(openList);
  LinkList *closeList = initList(closeList);
  LinkList *path = NULL;//指针，对应的内存空间在generatePath中生成
  
  Grid src,dest;//起始、目标格
  Grid *current;//当前格 指针
  Grid tempGrid;//暂存
  Grid neighbors[4];//存储当前邻居格

  //current = src;//初始化current为起点
  src.loc = Psrc;
  dest.loc = Pdest;
  src.G = 0;
  src.H = getDistance_Manhattan(src.loc,dest.loc);
  src.F = src.G + src.H;

  insertLinkList(openList,1,src);//open链表放入起始点
  //此时open应当不空
  while (!isEmpty(openList)){
    current = getMinCostGrid(openList);//取当前openlist中代价最小格
    if(isSamePosition(current->loc,dest.loc))//当前格就是目标格，返回目标格链表
    {
      path = generatePath(dest);//生成路径并将地址传给path
      break;//准备输出path
    }else if(getStepDirect(current->loc,Pdest)!=-1){
      dest.father = current;//让目标格指向当前格
      path = generatePath(dest);//生成路径并将地址传给path
      break;//准备输出path
    }

    //tempMinCost = *searchMinGrid(openList);

      for(int i;i<4;i++){
        switch (i)
        {
          case NEIGHBOR_LEFT:
            neighbors[i].loc.y = current->loc.y-1;break;
          case NEIGHBOR_RIGHT:
            neighbors[i].loc.y = current->loc.y+1;break;
          case NEIGHBOR_UP:
            neighbors[i].loc.x = current->loc.x-1;break;
          case NEIGHBOR_DOWN:
            neighbors[i].loc.x = current->loc.x+1;break;
          default:break;
        }
        if(isValidGrid(map, neighbors->loc)){//返回1（可行走格）时
          neighbors[i].father = current;
          //neighbors[i].typeOfgrid = 0;
          neighbors[i].inClose = 0;
          neighbors[i].inOpen = 0;//完善结构体数据
          
          //计算G,便于判断
          neighbors[i].G = current->G + MOVE_COST;

          if(neighbors[i].inOpen == 1){//if neighbor in OPEN
            if(neighbors[i].G < searchLinkList(openList,neighbors[i])->grid.G){//and cost less than g(neighbor):
              // remove neighbor from OPEN, because new path is better
              neighbors[i].inOpen = 0;
              neighbors[i].inClose = 1;
              deletLinkListByGrid(openList,neighbors[i]);
              insertLinkList(closeList,1,neighbors[i]);
            }
          }else if(neighbors[i].inClose == 1){//if neighbor in CLOSED 
            if(neighbors[i].G < searchLinkList(closeList,neighbors[i])->grid.G){// and cost less than g(neighbor):
            //remove neighbor from CLOSED
              neighbors[i].inOpen = 1;
              neighbors[i].inClose = 0;
              deletLinkListByGrid(openList,neighbors[i]);
              insertLinkList(openList,1,neighbors[i]);
            }
          }else{//neighbor 是新格子:
            neighbors[i].H = getDistance_Manhattan(neighbors[i].loc,dest.loc);
            neighbors[i].F = neighbors[i].G + neighbors[i].H;
            insertLinkList(openList,1,neighbors[i]);    //add neighbor to OPEN
          }
        }
        else{
          //neighbors[i].typeOfgrid = 1;
          continue;//对下一个邻居进行判断
        }
      }
      
      deletLinkListByPoint(openList,current->loc);
      insertLinkList(closeList,getLen(closeList),*current);
      current->inClose = 1;
      current->inOpen = 0;
  };//跳出循环说明已经遍历完open表也到达不了目标点
  free(openList);
  free(closeList);
  return path;
}

//返回F最小值链表(最短为1，并且按G排序)
LinkList* getGrids_minF(LinkList *L){
    LinkList *r = L, *minnode = NULL;//
    LinkList *path = initList(path);
    int currentminF = L->grid.F;
    int currentminG = L->grid.G;
    while(r->next != NULL){
        if((r->grid.F < currentminF) || (r->grid.F == currentminF && r->grid.G < currentminG)){
            currentminF = r->grid.F;
            currentminG = r->grid.G;
            minnode = r;
        }
        else if(r->grid.F == currentminF && r->grid.G == currentminG){
            LinkList *newnode = (LinkList *)malloc(sizeof(LinkList));
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
//默认current已经是到目标点上了，迭代father,返回一条新的路径，此函数只在astar.c使用
LinkList* generatePath(Grid temp){//传入current的拷贝
  LinkList *path = initList(path);
  do
  {
    insertLinkList(path,1,temp);
    if(temp.father != NULL)temp = *temp.father;
    else break;
  }while(1);
  reverseLinkList(path);
  return path;//起点到终点的路径，包含起点与终点
}
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
//输入地图，起止点，返回起点到终点的路径，包括起点与终点格，至少一格，不可达到为NULL 注意调用后需要清理不用的链表!
LinkList* aStarSearch(Map *map, Point Psrc, Point Pdest){
//int max_nodes = map.length * map[0].length;

  LinkList *openList = initList(openList);
  LinkList *closeList = initList(closeList);
  LinkList *path = NULL;//指针，对应的内存空间在generatePath中生成
  
  Grid src,dest;//起始、目标格
  Grid *current;//当前格 指针
  LinkList* tempLink;//暂存
  Grid neighbor;//存储当前邻居格
  Grid neighborAgain;
  int neighborIsAgain;//0新 1在open 2在close

  //current = src;//初始化current为起点
  dest.loc = Pdest;
  src.loc = Psrc;
  src.father = NULL;
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

      for(int i=0;i<4;i++){
        neighbor.loc = current->loc;
        switch (i)
        {
          case NEIGHBOR_LEFT:
            neighbor.loc.y -= 1;break;
          case NEIGHBOR_RIGHT:
            neighbor.loc.y += 1;break;
          case NEIGHBOR_UP:
            neighbor.loc.x -= 1;break;
          case NEIGHBOR_DOWN:
            neighbor.loc.x += 1;break;
          default:break;
        }
        if(isValidGrid(map, neighbor.loc)){//返回1（可行走格）时
          neighborIsAgain = 0;
          neighbor.father = current;
          tempLink = searchLinkList(openList,neighbor);
          if(!(tempLink==NULL)) {//已经在open表
            neighborIsAgain = 1;
            neighborAgain = tempLink->grid;
            neighbor.G = current->G + MOVE_COST;//计算G,便于判断
          }else{
            tempLink = searchLinkList(closeList,neighbor);
            if(!(tempLink==NULL)){//已经在close表
              neighborIsAgain = 2;
              neighborAgain =tempLink->grid;
              neighbor.G = current->G + MOVE_COST;//计算G,便于判断
            }
          }
          switch (neighborIsAgain)
          {
          case 0://neighbor 是新格子:
            neighbor.G = current->G + MOVE_COST;//计算G,便于判断
            neighbor.H = getDistance_Manhattan(neighbor.loc,dest.loc);
            neighbor.F = neighbor.G + neighbor.H;
            insertLinkList(openList,1,neighbor);//加入新邻居到open
            break;
          case 1://
            if(neighbor.G < neighborAgain.G){//新路线比原open表内格点好
              insertLinkList(closeList,1,neighbor);
              deletLinkListByGrid(openList,neighborAgain);
            }
            break;
          case 2:
            if(neighbor.G < neighborAgain.G){// 新路线比原close表内格点好
              insertLinkList(openList,1,neighbor);
              deletLinkListByGrid(openList,neighborAgain);
            } 
            break;
          default:
            break;
          }
        }
        else{
          //该邻居不可用
          continue;//对下一个邻居进行判断
        }
      }
      
      insertLinkList(closeList,1,*current);
      deletLinkListByPoint(openList,current->loc);
  };//跳出循环说明已经遍历完open表也到达不了目标点
  // free(openList);
  // free(closeList);释放空表
  deleteLink_Grid(openList);
  deleteLink_Grid(closeList);
  return path;
}

//返回F最小值链表(最短为1，并且按G排序)
LinkList* getGrids_minF(LinkList *L){
    LinkList *r = L, *minnode = NULL;
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
    free(path);
    deleteLink_Grid(path);
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
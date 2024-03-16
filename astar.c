#include "astar.h"

#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>


#define VALUE_INF 65535
#define NEIGHBOR_LEFT 0
#define NEIGHBOR_RIGHT 1
#define NEIGHBOR_UP 2
#define NEIGHBOR_DOWN 3

#define MOVE_COST 10

int isValidGrid(Map *map, Point point){
  char target = map->data[point.x][point.y];
  if (target=="."){return 1;}
  else{return 0;}
}
int getcostH(Point start, Point end){//???待修改
    int hdistance;
    hdistance = abs(start.x - end.x) + abs(start.y - end.y);
    return hdistance;
}
LinkList* aStarSearch(Map *map, Grid src, Grid dest){//传入指针???
//int max_nodes = map.length * map[0].length;

  LinkList *openList = initList(openList);
  LinkList *closeList = initList(closeList);
  LinkList *path = initList(path);
  src.father = NULL;
  src.G = 0;
  src.H = getcostH(src.loc,dest.loc);
  src.F = src.G + src.H;

  Grid neighbors[4];//存储目标邻居格
  Grid current = src;//初始化current为起点
  Grid temp;

  insertLinkList(openList,1,&src);//初始化open链表

  while (searchLinkList(openList,dest)!=NULL)// while()lowest rank in OPEN is not the GOAL:???
  {
    // current = remove lowest rank item from OPEN  
    // add current to CLOSED
    LinkList* current = searchMinList(openList);//找出最小F的格子，可能多个  //???current和内部重名，open表删除current时机调整
    while(current->next != NULL){

      deletLinkByXY(openList,current->grid);
      insertLinkList(closeList,getLen(closeList),&current);
      current->grid.inClose = 1;
      current->grid.inOpen = 0;

        for(int i;i<4;i++){
          switch (i)
          {
            case NEIGHBOR_LEFT:
              neighbors[i].loc.y = current->grid.loc.y-1;break;
            case NEIGHBOR_RIGHT:
              neighbors[i].loc.y = current->grid.loc.y+1;break;
            case NEIGHBOR_UP:
              neighbors[i].loc.x = current->grid.loc.x-1;break;
            case NEIGHBOR_DOWN:
              neighbors[i].loc.x = current->grid.loc.x+1;break;
            default:break;
          }
          if(isValidGrid(map, neighbors->loc)){//返回1（可行走格）时
            neighbors[i].father = &current;
            //neighbors[i].typeOfgrid = 0;
            neighbors[i].inClose = 0;
            neighbors[i].inOpen = 0;//完善结构体数据
            
            //计算G,便于判断
            neighbors[i].G = current->grid.G + MOVE_COST;

            if(neighbors[i].inOpen == 1){//if neighbor in OPEN
              if(neighbors[i].G < searchLinkList(openList,neighbors[i])->grid.G){//and cost less than g(neighbor):
                // remove neighbor from OPEN, because new path is better
                neighbors[i].inOpen = 0;
                neighbors[i].inClose = 1;
                deleteLinkList(openList,&neighbors[i]);
                insertLinkList(closeList,1,&neighbors[i]);
              }
            }else if(neighbors[i].inClose == 1){//if neighbor in CLOSED 
              if(neighbors[i].G < searchLinkList(closeList,neighbors[i])->grid.G){// and cost less than g(neighbor):
              //remove neighbor from CLOSED
                neighbors[i].inOpen = 1;
                neighbors[i].inClose = 0;
                deleteLinkList(closeList,&neighbors[i]);
                insertLinkList(openList,1,&neighbors[i]);
              }
            }else{//neighbor 是新格子:
              neighbors[i].H = getcostH(neighbors[i].loc,dest.loc);
              neighbors[i].F = neighbors[i].G + neighbors[i].H;
              insertLinkList(openList,1,&neighbors[i]);    //add neighbor to OPEN
            }
          }
          else{
            //neighbors[i].typeOfgrid = 1;
            continue;//对下一个邻居进行判断
          }
      }
      deleteLinkList(openList)
      current = current->next;    
    }
  }

  dest.father = &current;//都采用指针
  temp = dest;
  while(temp.father != NULL){
    insertLinkList(path,1,&temp);
    temp = *temp.father;
  }
  reverseLinkList(path);
  return path;//起点到终点的路径，包含起点与终点
}



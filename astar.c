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

int isValideGrid(Map *map, int x,int y){
  char target = map->data[x][y];
  if (target=="."){return 1;}
  else{return 0;}
}
int getcostH(Grid *start, Goods *end){
    int hdistance;
    hdistance = abs(start->x - end->x) + abs(start->y - end->y);
    return hdistance;
}
LinkList aStarSearch(Map *map, Grid src, Grid dest){
//int max_nodes = map.length * map[0].length;

  LinkList *openList = initList(openList);
  LinkList *closeList = initList(closeList);
  LinkList *path = initList(path);
  src.father = NULL;
  src.G = 0;
  src.H = getcostH(&src,&dest);
  src.F = src.G + src.H;

  Grid neighbors[4];//存储目标邻居格
  Grid current = src;//初始化current为起点
  Grid temp;


  insertLinkList(openList,1,&src);//初始化open链表

  while (searchLinkList(openList,dest)!=NULL)// while()lowest rank in OPEN is not the GOAL:
  {
    // current = remove lowest rank item from OPEN  
    // add current to CLOSED
    Grid current;
    int currentPos = minList(openList);//???
    deleteLinkList(openList,currentPos);
    insertLinkList(closeList,getLen(closeList),&current);
    current.inClose = 1;
    current.inOpen = 0;
  
    // for neighbors of current:
    for(int i;i<4;i++){
      switch (i)
      {
        case NEIGHBOR_LEFT:
          neighbors[i].y = current.y-1;break;
        case NEIGHBOR_RIGHT:
          neighbors[i].y = current.y+1;break;
        case NEIGHBOR_UP:
          neighbors[i].x = current.x-1;break;
        case NEIGHBOR_DOWN:
          neighbors[i].x = current.x+1;break;
        default:break;
      }
      if(isValidGrid(map, neighbors[i].x, neighbors[i].y)){//返回1（可行走格）时
        neighbors[i].father = &current;
        neighbors[i].typeOfgrid = 0;
        neighbors[i].inClose = 0;
        neighbors[i].inOpen = 0;//完善结构体数据
        
        //计算G,便于判断
        neighbors[i].G = current.G + MOVE_COST;

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
          neighbors[i].H = getcostH(&neighbors[i],&dest);
          neighbors[i].F = neighbors[i].G + neighbors[i].H;
          insertLinkList(openList,1,&neighbors[i]);    //add neighbor to OPEN
        }
      }
      else{
        neighbors[i].typeOfgrid = 1;continue;//对下一个邻居进行判断
      }
    }
  }

  dest.father = &current;//都采用指针
  temp = dest;
  while(temp.father != NULL){
    insertLinkList(path,1,&temp);
    temp = *temp.father;
  }
}



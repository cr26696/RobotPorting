#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>


#define value_inf 65535;
#define LEFT 0;
#define RIGHT 1;
#define UP 2;
#define DOWN 3;



// int isValid(int row, int col);//越界判断
// int calculateHValue(int row, int col, Pos dest);//H值计算函数
// void tracePath(Node nodeDetails[][COL], Pos dest);//回溯生成path

int isValueGrid(int x,int y){
  //?????????????
}

void aStarSearch(Grid src, Grid dest){/*************地图参数？？？****************/
//int max_nodes = map.length * map[0].length;

  LinkList *openList = initList(openList);  //OPEN = priority queue containing START
  LinkList *closeList = initList(closeList);//   //CLOSED = empty set

  Grid neighbors[4];
  Grid current = src;

  //node startNode;
  // startNode.father = &startNode;
  // startNode.F = value_inf;
  // startNode.G = value_inf;
  // startNode.H = value_inf;
  // startNode.inOpen = 0;
  // startNode.inClose = 0;

  
  insertLinkList(openList,1,src);

  
  while (seachLinkList(openList,dest)!=NULL)// while()lowest rank in OPEN is not the GOAL:
  {

    // current = remove lowest rank item from OPEN  
     // add current to CLOSED
    Grid current;
    int currentPos = minList(openList);//???
    deleteLinkList(openList,currentPos,&current);
    insertLinkList(closeList,getLen(closeList),&current);
    current.inClose = 1;
    current.inOpen = 0;
  
  // for neighbors of current:
    for(int i;i<4;i++){
      
      if(isValueGrid(i.x, i.y)){
        if(i=LEFT){neighbors[i].y = current.y -1;}
        if(i=rginth){neighbors[i].y = current.y -1;}
        if(i=LEFT){neighbors[i].y = current.y -1;}
        if(i=LEFT){neighbors[i].y = current.y -1;}

        neighbors[i].father = &current;
        neighbors[i].typeOfgrid = 0;
        neighbors[i].inClose = 0;
        neighbors[i].inOpen = 0;
        
        //   cost = g(current) + movementcost(current, neighbor)
        //???计算G,H,F
      }
      else{
      neighbors[i].typeOfgrid = 1;
      }
        //   if neighbor in OPEN and cost less than g(neighbor):

      if(neighbors[i].inOpen == 1){
        // remove neighbor from OPEN, because new path is better
      }

      //if neighbor in CLOSED 
      else if(neighbors[i].inClose == 1){
      // and cost less than g(neighbor): **
      if(current.G + 10 < seachLinkList(closeList,neighbors[i])->grid.G){
        Grid temp;
      //remove neighbor from CLOSED
        deleteLinkList(closeList,neighbors);//???
      }
    }
  //   if neighbor not in OPEN and neighbor not in CLOSED:
      else {
  //     set g(neighbor) to cost
        neighbors[i].G = current.G + 10;
        //???写入H
  //     add neighbor to OPEN
        insertLinkList(openList,1,neighbors[i]);
  //     set priority queue rank to g(neighbor) + h(neighbor)

      }
    }
  }
}

void getFdistance(Grid *grid, Goods *goods){
    int hdistance;
    hdistance = abs(grid->x - goods->x) + abs(grid->y - goods->y);
}
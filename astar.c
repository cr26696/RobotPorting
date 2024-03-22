#include "astar.h"

#define VALUE_INF 65535
#define NEIGHBOR_LEFT 0
#define NEIGHBOR_RIGHT 1
#define NEIGHBOR_UP 2
#define NEIGHBOR_DOWN 3

extern Grid gridMap[200][200];

#define MOVE_COST 10
//传入地图，目标点，返回1可走 0不可走
int isValidGrid(Map *map, Point point){
  char target = map->data[point.x][point.y];
  if (target=='.' || target=='A' || target=='B'){return 1;}
  else{return 0;}
}
//输入地图，起止点，返回起点到终点的路径，包括起点与终点格，至少一格，不可达到为NULL 注意调用后需要清理不用的链表!
LinkPath* aStarSearch(Map *map, /*Grid** gridMap,*/ Point Psrc, Point Pdest){
//int max_nodes = map.length * map[0].length;


  int openLen,closeLen,pathLen;

  LinkGrid *openList = LinkInit_Grid(openList);
  LinkGrid *closeList = LinkInit_Grid(closeList);
  LinkPath* path= NULL;//指针，对应的内存空间在generatePath中生成
  
  Grid *src=&gridMap[Psrc.x][Psrc.y],*dest=&gridMap[Pdest.x][Pdest.y];//起始、目标格
  Grid *current;//当前格
  LinkGrid* tempLink;//暂存
  Grid tempGrid;//存储当前邻居格
  Grid* pTempGrid;
  int neighborIsAgain;//0新 1在open 2在close

  //current = src;//初始化current为起点
  src->loc = Psrc;

  dest->loc = Pdest;
//  dest->loc.y = Pdest.y;
  src->father = src->loc;
//  src->father.y = src->loc.y;
  src->G = 0;
  src->H = getDistance_Manhattan(src->loc,dest->loc)*9;
  src->F = src->G + src->H;

  LinkInsert_ByIndex_Grid(openList,1,src);//open链表放入起始点
  openLen = LinkGetLen_Grid(openList);
  //此时open应当不空
  while (!LinkIsEmpty_Grid(openList)){
    current = ListgetMinCostGrid_Grid(openList);//取当前openlist中代价最小格
    if(isSamePosition(current->loc,dest->loc))//当前格就是目标格，返回目标格链表
    {
      path = generatePath(dest);//生成路径并将地址传给path
      break;//准备输出path
    }else if(getStepDirect(current->loc,Pdest)!=-1){
      dest->father = current->loc;//让目标格指向当前格
      dest->father.x = current->loc.x;//让目标格指向当前格
      dest->father.y = current->loc.y;//让目标格指向当前格
      path = generatePath(dest);//生成路径并将地址传给path
      break;//准备输出path
    }

    //tempMinCost = *searchMinGrid(openList);

      for(int i=0;i<4;i++){
        tempGrid.loc = current->loc;//临时点为邻居点
        switch (i)
        {
          case NEIGHBOR_LEFT:
            tempGrid.loc.y -= 1;break;
          case NEIGHBOR_RIGHT:
            tempGrid.loc.y += 1;break;
          case NEIGHBOR_UP:
            tempGrid.loc.x -= 1;break;
          case NEIGHBOR_DOWN:
            tempGrid.loc.x += 1;break;
          default:break;
        }
        if(isValidGrid(map, tempGrid.loc)){//返回1（可行走格）时
          neighborIsAgain = 0;
          tempLink = LinksearchLink_ByObj_Grid(openList,&tempGrid);//返回open表的片段
          if(!(tempLink==NULL)) {//已经在open表
            neighborIsAgain = 1;
            pTempGrid = tempLink->grid;
            tempGrid.G = current->G + MOVE_COST;//计算G,便于判断
          }else{
            tempLink = LinksearchLink_ByObj_Grid(closeList,&tempGrid);
            if(!(tempLink==NULL)){//已经在close表
              neighborIsAgain = 2;
              pTempGrid = tempLink->grid;
              tempGrid.G = current->G + MOVE_COST;
            }
          }
          switch (neighborIsAgain)
          {
          case 0://neighbor 是新格子:
            //不在open close表，从总表查出
            pTempGrid = &gridMap[tempGrid.loc.x][tempGrid.loc.y];
            pTempGrid->loc = tempGrid.loc;
            pTempGrid->G = current->G + MOVE_COST;
            pTempGrid->H = getDistance_Manhattan(pTempGrid->loc,Pdest)*9;
            pTempGrid->F = pTempGrid->G + pTempGrid->H;
            pTempGrid->father = current->loc;
            LinkInsert_ByIndex_Grid(openList,1,pTempGrid);//加入新邻居到open
            openLen = LinkGetLen_Grid(openList);
            break;
          case 1://
            if(tempGrid.G < pTempGrid->G){//新路线比原open表内格点好
              pTempGrid->loc = tempGrid.loc;
              pTempGrid->father = tempGrid.father;
              pTempGrid->G = tempGrid.G;
              pTempGrid->G = pTempGrid->G + pTempGrid->H;
              // LinkInsert_ByIndex_Grid(closeList,1,neighbor);
              // deletLinkPathByGrid(openList,pAgainGrid);
            }
            break;
          case 2:
            if(tempGrid.G < pTempGrid->G){// 新路线比原close表内格点好
              pTempGrid->loc = tempGrid.loc;
              pTempGrid->father = tempGrid.father;
              pTempGrid->G = tempGrid.G;
              pTempGrid->G = pTempGrid->G + pTempGrid->H;
              LinkInsert_ByIndex_Grid(openList,1,pTempGrid);
              LinkSoftDelete_ByObj_Grid(closeList,pTempGrid);
              openLen = LinkGetLen_Grid(openList);
              closeLen = LinkGetLen_Grid(closeList);
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
      
      LinkSoftDelete_ByObj_Grid(openList,current);
      openLen = LinkGetLen_Grid(openList);
      LinkInsert_ByIndex_Grid(closeList,1,current);
      closeLen = LinkGetLen_Grid(closeList);
  };//跳出循环说明已经遍历完open表也到达不了目标点
  // free(openList);
  // free(closeList);释放空表
  LinkSoftDelete_Grid(openList);
  LinkSoftDelete_Grid(closeList);
  return path;
}

//返回F最小值链表(最短为1，并且按G排序)


//默认current已经是到目标点上了，迭代father,返回一条新的路径
LinkPath* generatePath(Grid *cur){
  Point tPoint;//暂存点
  LinkPath* path = linkInit_Path(path);
  linkInsert_byPos_Path(path,1,cur->loc);
  tPoint = cur->father;
  while(!isSamePosition(tPoint,cur->loc)){
    cur = &gridMap[tPoint.x][tPoint.y];
    linkInsert_byPos_Path(path,1,tPoint);
    tPoint = cur->father;
  }
  return path;
}
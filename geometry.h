#ifndef GEOMETRY_H//预定义避免重复引入
#define GEOMETRY_H

// #include <math.h>
//int型内含x,y
typedef struct Point
{
  int x;
  int y;
}Point;
//寻路算法所用格点，内含坐标Pos,父格点指针
typedef struct Grid {
    Point loc;
    struct Grid* father;//父格点地址
    int G, F, H;
    int inOpen,inClose;
    // int typeOfgrid;//格子类型？
}Grid;

Point createPoint(int x,int y);

//Grid *createGrid(int x,int y);

int isSamePosition(Point A, Point B);

int isNeighbor(Point A, Point B);

int getDistance_Manhattan(Point start, Point end);

int getStepDirect(Point start,Point next);


#endif
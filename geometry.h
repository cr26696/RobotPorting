#ifndef GEOMETRY_H//预定义避免重复引入
#define GEOMETRY_H
#include <malloc.h>
//int型内含x,y
typedef struct Point
{
  int x;
  int y;
}Point;

Point *createPoint(int x,int y);

int getDistance_Manhattan(Point start, Point end);

int getStepDirect(Point start,Point next);

#endif
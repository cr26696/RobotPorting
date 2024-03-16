#ifndef GEOMETRY_H//预定义避免重复引入
#define GEOMETRY_H
#include <malloc.h>
//int型内含x,y
typedef struct Point
{
  int x;
  int y;
}Point;
//传入x,y 返回一个Point
Point *createPoint(int x,int y){
  Point *ptr = (Point *)malloc(sizeof(Point));
  ptr->x = x;
  ptr->x = y;
  return ptr;
}

#endif
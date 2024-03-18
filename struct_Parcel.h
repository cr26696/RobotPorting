#ifndef STRUCT_PARCEL_H//预定义避免重复引入
#define STRUCT_PARCEL_H

#include "geometry.h"
typedef struct Parcel
{
  int addedFrame;//添加时间
  int value;//价值
  Point loc;//
}Parcel;

#endif
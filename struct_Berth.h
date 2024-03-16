#ifndef STRUCT_Berth_H//预定义避免重复引入
#define STRUCT_Berth_H

#include "geometry.h"
typedef struct Berth
{
  int id;//泊位号
  Point pos;
  int transport_time;//泊口运出速度
  int loading_speed;//泊口装货速度
  int goodsnum;//泊口货物的数量
  int status;//泊位状态，1为空闲，0为占用
}Berth;

#endif
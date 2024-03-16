#ifndef STRUCT_Berth_H//预定义避免重复引入
#define STRUCT_Berth_H

#include "geometry.h"
typedef struct Berth
{
  Point pos;
  int transport_time;//泊口运出速度
  int loading_speed;//泊口装货速度
}Berth;

#endif
#ifndef STRUCT_GRID_H//预定义避免重复引入
#define STRUCT_GRID_H

#include "geometry.h"

typedef struct Grid {
    Point loc;
    Point father;//父格点地址
    int G, F, H;
}Grid;

#endif
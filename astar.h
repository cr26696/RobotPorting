#ifndef ASTAR_H//预定义避免重复引入
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h" 
#include "struct_Map.h"

int isValueGrid(int x,int y);//
void aStarSearch(Map *map, Grid src, Grid dest);//返回一个path
void getFdistance(Grid *grid, Goods *goods);//计算F通过指针传入grid

//*map 结构体使用列：

// void processMap(Map *map) {
//     // 在这里处理地图数据
//     // map->data[i][j] 表示第 i 行、第 j 列的元素
// }

// int main() {
//     Map myMap; // 创建一个地图结构体
//     // 初始化地图数据
//     // ...

//     processMap(&myMap); // 将地图结构体传递给函数
//     return 0;
// }



#endif
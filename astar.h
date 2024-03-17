#ifndef ASTAR_H//预定义避免重复引入
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h" 
#include "geometry.h" 
#include "struct_Map.h"

int isValidGrid(Map *map, Point point);//返回1表示空地
LinkList* aStarSearch(Map *map, Point Psrc, Point Pdest);//返回一个path

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
#ifndef ASTAR_H//预定义避免重复引入
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h" 
#include "struct_Map.h"

int isValideGrid(Map *map, int x, int y);//返回1表示空地
int getcostH(Grid *start, Goods *end);//传入起、止两点指针，计算H并返回
LinkList* aStarSearch(Map *map, Grid src, Grid dest);//返回一个path

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
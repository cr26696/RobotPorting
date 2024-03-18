#ifndef STRUCT_MAP_H//预定义避免重复引入
#define STRUCT_MAP_H

#define MAP_ROWS  200
#define MAP_COLS  200

typedef struct Map{
    char data[MAP_ROWS][MAP_COLS];
}Map;

#endif
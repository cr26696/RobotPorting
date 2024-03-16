#include "struct_Robot.h"
#include "astar.h"

#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>
const int robot_num = 10;
Robot robot[robot_num];

void robotStateInit()
{
    for (int i = 0; i < robot_num; i++)
    {
        // aStarSearch(&map,robot[i].)
        if () // 没有到泊口的路
        {robot[i].status = ROBOT_STUCK;}
    }
}
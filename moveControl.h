#ifndef MOVE_CONTROL_H//预定义避免重复引入
#define MOVE_CONTROL_H

#include <stdio.h>

#include "list.h"
#include "struct_Robot.h"

void moveRobot(Robot *robot, LinkList *path);

#endif
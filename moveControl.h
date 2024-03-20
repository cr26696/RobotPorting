#ifndef MOVE_CONTROL_H//预定义避免重复引入
#define MOVE_CONTROL_H

#include <stdio.h>

#include "LinkPath.h"
#include "struct_Robot.h"

void updateRobotDirect(Robot *robot, LinkPath *path);

#endif
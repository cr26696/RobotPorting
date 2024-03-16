#include "moveControl.h"
//输入机器人结构体指针，路径链表指针，更新机器人下一步运动方向
void moveRobot(Robot *robot, LinkList *path)
{
  int curX, curY, destX, destY;//当前XY，路径目标XY
  int curX = robot->x;
  int curY = robot->y;
  path = path->next;//链表位置移动
  int destX = path->grid.x;
  int destY = path->grid.x;//得到相邻两格坐标
  if(curX==destX){//将相邻两格坐标转化为移动方向
    switch (curX-destX)
    {
    case -1:
      robot->direct = MOVE_DOWN;break;
    case 1:
      robot->direct = MOVE_UP;break;
    default:break;
    }
  }else if(curY==destY){
    switch (curY-destY)
      {
      case -1:
        robot->direct = MOVE_RIGHT;break;
      case 1:
        robot->direct = MOVE_LEFT;break;
      default:break;
      }
  }else{//不应该出现这种情况(即两个格子不相邻)
  }
}
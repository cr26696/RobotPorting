#include "moveControl.h"
//输入机器人结构体指针，路径链表指针，更新机器人下一步运动方向,并将链表向后移动
void updateRobotDirect(Robot *robot, LinkList *path)
{
  //当前点，下一步点
  Point Pstart = path->grid.loc;
  path = path->next;//path链表位置移动到next
  Point Pnext = path->grid.loc;

  robot->direct = getStepDirect(Pstart,Pnext);
}

// Point getRobotNextPathPoint(Robot *rob, LinkList *path){
//   LinkList *temppath = path;
//   temppath->next->grid.loc;
// }
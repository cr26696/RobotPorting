#include "moveControl.h"
//输入机器人结构体指针，路径链表指针（不存在空的头部链表结点），更新机器人下一步运动方向,不操作路径链表 
void updateRobotDirect(Robot *robot, LinkPath *path)
{
  //当前点，下一步点
  Point Pstart = path->pos;
  //path链表位置移动到next
  Point Pnext = path->next->pos;

  robot->action = getStepDirect(Pstart,Pnext);
}

// Point getRobotNextPathPoint(Robot *rob, LinkPath *path){
//   LinkPath *temppath = path;
//   temppath->next->pos;
// }
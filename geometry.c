#include "geometry.h"

#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_UP 3
#define MOVE_DOWN 4

//分配内存，输入x,y 返回一个Point类型指针
Point *createPoint(int x,int y){
  Point *ptr = (Point *)malloc(sizeof(Point));
  ptr->x = x;
  ptr->x = y;
  return ptr;
}
//分配内存，输入相关参数，返回一个Grid类型指针
Grid *createGrid(int x,int y){
  
}
//判断两点坐标相同，1相同，0不同
int isSamePosition(Point A, Point B){
  if(A.x == B.x && A.y == B.y)return 1;
  else return 0;
}
//输入两个Point类型，返回曼哈顿距离(H估值)
int getDistance_Manhattan(Point start, Point end){
    int hdistance;
    hdistance = abs(start.x - end.x) + abs(start.y - end.y);
    return hdistance;
}
//输入两相邻Point,返回下一步方向 左1 右2 上3 下4 输入点有误-1 也可用于判断两点是否相邻
int getStepDirect(Point Pstart, Point Pnext){
  int direct;
  if(Pstart.x==Pnext.x){//将相邻两格坐标转化为移动方向
    switch (Pstart.x-Pnext.x)
    {
    case -1:
      direct = MOVE_DOWN;break;
    case 1:
      direct = MOVE_UP;break;
    default:break;
    }
  }else if(Pstart.y==Pnext.y){
    switch (Pstart.y-Pnext.y)
      {
      case -1:
        direct = MOVE_RIGHT;break;
      case 1:
        direct = MOVE_LEFT;break;
      default:break;
      }
  }else{
    direct = -1;//不应该出现这种情况(即两个格子不相邻)
  }
  return direct;
}
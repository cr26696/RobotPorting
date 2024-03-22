#include "geometry.h"

//返回一个Point类型引用
Point createPoint(int x,int y){
  Point ptr;
  ptr.x = x;
  ptr.y = y;
  return ptr;
}

//判断两点坐标相同，1相同，0不同
int isSamePosition(Point A, Point B){
  if(A.x == B.x && A.y == B.y)return 1;
  else return 0;
}
//相邻返回1，相等或不相邻返回0
int isNeighbor(Point A, Point B){
  if(abs(A.x - B.x) == 1){
    if(A.y == B.y) return 1;//x相差1且y相等
  }else if(abs(A.y - B.y) == 1){
    if(A.x == B.x) return 1;//y相差1且x相等
  }
  return 0;
}
//输入两个Point类型，返回曼哈顿距离(H估值)
int getDistance_Manhattan(Point start, Point end){
    int hdistance;
    hdistance = abs(start.x - end.x) + abs(start.y - end.y);
    return hdistance;
}
//输入两相邻Point,返回下一步方向  枚举类型direction 左1 右2 上3 下4 输入点有误返回int -1 也可用于判断两点是否相邻
int getStepDirect(Point Pstart, Point Pnext){
  direction direct;
  if(Pstart.y==Pnext.y){//将相邻两格坐标转化为移动方向
    switch (Pstart.x-Pnext.x)
    {
    case -1:
      direct = down;break;
    case 1:
      direct = up;break;
    default:break;
    }
  }else if(Pstart.x==Pnext.x){
    switch (Pstart.y-Pnext.y)
      {
      case -1:
        direct = right;break;
      case 1:
        direct = left;break;
      default:break;
      }
  // }else{
  //   direct = wait;//不应该出现这种情况(即两个格子不相邻)
  }else return -1;
  return direct;
}
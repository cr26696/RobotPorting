#include "pointerList.h"

/*指针数组 插入指针(从0开始,插在原元素前) 返回值成功1失败0 
len为实际存储元素"个数"
*/
int pointerlistInsert(void* list[],int len,int pos,void* ptr){
  if(pos < 0 || pos > len - 1) return 0;//越界
  for(;len>pos;len--){
    list[len] = list[len-1];
  }
  void* temp;
  temp = list[pos];
  list[pos] = ptr; //插入完成
  //移动后面部分
  pos++;
  temp = list[pos]
  list
}
#include "struct_Boat.h"
#include "struct_Berth.h"

#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>

int leaveberth (Boat *boat ,Berth *berth){//???泊口的货物数
    if( boat->goodsnum>=10 && berth->goodsnum==0){
        boat->status=0;//船在运输状态???或者main函数里写
        boat->pos=-1;//船目标泊位虚拟点
        return 1;}
}

void countgoodsnum(Berth *berth,Boat *boat){//计算泊口的货物数量和船上的货物数量
     boat->goodsnum=boat->goodsnum+berth->goodsnum;
     berth->goodsnum=berth->goodsnum-berth->loading_speed;
}

void gotoberth(Berth *berth[]) //结构体数组调用 输出 ???船去货物多的（货物选择泊口的时候选择港口运输时间少，并且
{
    const int berth_num = 10;
    const int boat_num = 5;
    Berth berth[berth_num];
    Boat boat[boat_num];
    int num;//需要分配泊口的船号

    if( 1 )//???船在虚拟点
    {
int maxgnum = 0; // 最大货物数
    int maxberth=0;//最多货物对应的港口
    for (int i = 0; i < berth_num; i++)
    {
        if (berth[i].status = 1)//泊口空闲
        {
            if(berth[i].goodsnum>maxgnum)//找出最多的货物
            {maxgnum=berth[i].goodsnum=maxgnum;
             maxberth=berth[i].id;
            }
        }
        else {continue;}
    }
    boat[num].pos=maxberth;
    berth[maxberth].status=0;    
    }
    
}

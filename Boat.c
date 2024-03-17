#include "struct_Boat.h"
#include "struct_Berth.h"


#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>

void boatStatusupdate(int backstatu,int aimId,Boat *boat)//船的状态判断
{
    if(backstatu==0 && aimId==-1){boat->status=TRANSPORT;}//从泊口到虚拟点途中
    if(backstatu==1 && aimId==-1){boat->status=ATVIRTUAL;}//到达虚拟点
    if(backstatu==0 && aimId!=1){boat->status=GOBACKBERTH;}//从虚拟点到泊口途中
    if(backstatu==1 && aimId!=1 ){boat->status=ATBERTH;}//到泊口，装载
    if(backstatu==2 && aimId!=1){boat->status=WAITING;}//到泊口等待(前面还有其他船)
    boat->aimId=aimId;
}

// int leaveberth (Boat *boat ,Berth *berth){//???泊口的货物数
//     if( boat->goodsnum>=10 && berth->goodsnum==0){
//         boat->status=0;//船在运输状态???或者main函数里写
//         boat->aimId=-1;//船目标泊位虚拟点
//         return 1;}
// }

void countgoodsnum(Berth *berth,Boat *boat){//计算泊口的货物数量和船上的货物数量
     boat->goodsnum=boat->goodsnum+berth->goodsnum;
     berth->goodsnum=berth->goodsnum-berth->loading_speed;
}

void controlBoat(Boat *boat[],int boat_num,Berth *berth[],int berth_num,int boat_capacity) //结构体数组调用 
{
    for (int i = 0; i < boat_num; i++)
    {
        // 船在虚拟点,船去货物多的泊口或者???运输时间最短的泊口
        if (boat[i]->status == ATVIRTUAL) 
        {
            int maxgnum = 0;  // 最大货物数
            int maxberth = 0; // 最多货物对应的港口
            for (int i = 0; i < berth_num; i++)
            {
                if (berth[i]->status = 1) // 泊口空闲
                {
                    if (berth[i]->goodsnum > maxgnum) // 找出最多的货物
                    {
                        maxgnum = berth[i]->goodsnum ;
                        maxberth = berth[i]->id;
                    }
                }
                else
                {continue;}
            }
            if (maxgnum != 0)
            {
                boat[i]->aimId = maxberth;
                printf("ship %d %d\n", i, boat[i]->aimId);
                boat[i]->status = GOBACKBERTH;
                berth[maxberth]->status = 0; // 对应港口锁定
            }
            else
            {
                int mintastime,mintastime_berth;//最少的运输时间和对应的泊口???还要考虑装载时间到时候改
                for (int i = 0; i < berth_num; i++)
                {
                    if (berth[i]->status = 1) // 泊口空闲 ???优化的时候考虑船到泊位的时间以及泊口船驶离的时间
                    {
                        if (berth[i]->transport_time) // 找出最多的货物
                    {
                        mintastime = berth[i]->transport_time;
                        mintastime_berth = berth[i]->id;
                    }
                    }
                }
                boat[i]->aimId = mintastime;
                printf("ship %d %d\n", i, boat[i]->aimId);
                boat[i]->status = GOBACKBERTH;
                berth[mintastime_berth]->status = 0; // 对应港口锁定
            }
        }
        
        //船在泊口，开始装货
        if (boat[i]->status == ATBERTH)
        {
            if (boat[i]->goodsnum < boat_capacity && berth[i]->goodsnum > 0) // 船上货物未满,泊口有货
            {
                countgoodsnum(boat[i], berth[boat[i]->aimId]); // 装载货物
            }
            else if (boat[i]->goodsnum = boat_capacity || berth[i]->goodsnum == 0) // 船在码头装载完成，去虚拟点//???优化等还有几步的机器人
            {
                printf("go %d\n", i);
                boat[i]->status = 0;               // 船在运输状态
                berth[boat[i]->aimId]->status = 1; // 对应港口空闲
                boat[i]->aimId = -1;               // 船目标泊位虚拟点
            }
        }
    }
}

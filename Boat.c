#include "Boat.h"

void boatStatusupdate(int backstatu,int aimId,Boat *boat)//船的状态判断
{
    if(backstatu==0 && aimId==-1){boat->status=TRANSPORT;}//去往虚拟点途中
    if(backstatu==1 && aimId==-1){boat->status=ATVIRTUAL;}//到达虚拟点
    if(backstatu==0 && aimId!=-1){boat->status=GOBACKBERTH;}//去往泊口途中
    if(backstatu==1 && aimId!=-1 ){boat->status=ATBERTH;}//到泊口，装载
    if(backstatu==2 && aimId!=-1){boat->status=WAITING;}//到泊口等待(前面还有其他船)
    boat->aimId=aimId;//目标泊位改变
    return ;
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

// 定义泊位的评估函数 值越大越好（参数分别代表：第一个因素装载速度，第一个因素的系数运输速度；第二个因素，第二个因素的系数...)
float evaluateBerth(int loadSpeed,float friscoe,int transportTime,float secocoe,int pathLength ,float thricoe)
{
    float totalScore;
    // double speedWeight = 0.4;     // 装载速度权重
    // double timeWeight = 0.3;      // 运输时间权重
    // double distanceWeight = 0.3;  // 路径长度权重

    // // 归一化处理，将值映射到0-1范围内（越小越好）
    // float normalizedSpeed = (5 - loadSpeed) / 4.0;
    // float normalizedTime = (transportTime - 1) / 999.0;
    // float normalizedDistance = (pathLength - 10) / 70.0;
    // //综合得分
    totalScore = (loadSpeed*friscoe) - (transportTime*secocoe) - (pathLength*thricoe);
    return totalScore;
}

void AllboatatVIRTUAL(Boat *boat,int boat_num,Berth berth[],int berth_num)
{
    int bestvual_berth;//最少的运输时间和最快的装载速度对应的泊口???还要考虑装载时间到时候改
    float bestvual,localberth_best;
    int berth_to_calc[10]={0};//空闲泊口数组，最多10个
    int cmArrLen=0;//custom Array Length
    int tempBerthId;//暂存id,随berth_to_calc变
    for(int i=0;i<berth_num;i++){
        if(berth[i].status){
            berth_to_calc[cmArrLen] = i;
            cmArrLen++;
        }
    }//将空闲泊口序号存入数组
    bestvual = -999;//初值，评价函数返回结果应该都会优于这个值
        for (int i = 0; i < cmArrLen; i++)
        {
            tempBerthId = berth_to_calc[i];
            localberth_best=evaluateBerth(berth[tempBerthId].loading_speed,0.1,berth[tempBerthId].transport_time,1,0,0);
            if (localberth_best>bestvual) // 找出最佳的港口
            {
                bestvual = localberth_best;
                bestvual_berth = berth[tempBerthId].id;
            }
        }
        boat->aimId = bestvual_berth;
        // printf("ship %d %d\n", i, boat[i].aimId);
        boat->status = GOBACKBERTH;
        berth[bestvual_berth].status = 0; // 对应港口锁定
}

void controlBoat(Boat boat[],int boat_num,Berth berth[],int berth_num,int boat_capacity) //结构体数组调用 
{
    for (int i = 0; i < boat_num; i++)
    {
        // 船在虚拟点,船去货物多的泊口或者???运输时间最短的泊口
        if (boat[i].status == ATVIRTUAL) 
        {
            int maxgnum = 0;  // 最大货物数
            int maxberth = 0; // 最多货物对应的港口
            for (int i = 0; i < berth_num; i++)
            {
                if (berth[i].status == 1) // 泊口空闲
                {
                    if (berth[i].goodsnum > maxgnum) // 找出最多的货物
                    {
                        maxgnum = berth[i].goodsnum ;
                        maxberth = berth[i].id;
                    }
                }
                else
                {continue;}
            }
            if (maxgnum != 0)
            {
                boat[i].aimId = maxberth;
                printf("ship %d %d\n", i, boat[i].aimId);
                boat[i].status = GOBACKBERTH;
                berth[maxberth].status = 0; // 对应港口锁定
            }
            else
            {
                AllboatatVIRTUAL(&boat[i],boat_num,berth,berth_num);
                printf("ship %d %d\n", i, boat[i].aimId);
                
                // int mintastime,mintastime_berth;//最少的运输时间和对应的泊口???还要考虑装载时间到时候改
                // for (int i = 0; i < berth_num; i++)
                // {
                //     if (berth[i].status == 1) // 泊口空闲 ???优化的时候考虑船到泊位的时间以及泊口船驶离的时间
                //     {
                //         if (berth[i].transport_time) // 找出最多的货物
                //     {
                //         mintastime = berth[i].transport_time;
                //         mintastime_berth = berth[i].id;
                //     }
                //     }
                // }
                // boat[i].aimId = mintastime;
                
                // boat[i].status = GOBACKBERTH;
                // berth[mintastime_berth].status = 0; // 对应港口锁定
            }
        }
        
        //船在泊口，开始装货
        if (boat[i].status == ATBERTH)
        {
            if (boat[i].goodsnum < boat_capacity && berth[i].goodsnum > 0) // 船上货物未满,泊口有货
            {
                countgoodsnum(&berth[boat[i].aimId],&boat[i]); // 装载货物
            }
            else if (boat[i].goodsnum == boat_capacity || berth[i].goodsnum == 0) // 船在码头装载完成，去虚拟点//???优化等还有几步的机器人
            {
                printf("go %d\n", i);
                boat[i].status = 0;               // 船在运输状态
                berth[boat[i].aimId].status = 1; // 对应港口空闲
                boat[i].aimId = -1;               // 船目标泊位虚拟点
            }
        }
    }
}
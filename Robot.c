#include "Robot.h"

const int robot_num = 10;
Robot robot[robot_num];

void robotstatusupdate(int carry,int stun ,Robot *robot)//机器人状态处理函数
{
    if(carry==0 && stun==0){robot->status=;}
    if(carry==0 && stun==0){robot->status=;}
    if(carry==0 && stun==0){robot->status=;}
    if(carry==0 && stun==0){robot->status=;}
    if(carry==0 && stun==0){robot->status=;}
    if(carry==0 && stun==0){robot->status=;}
}

// void robotStateInit()
// {
//     for (int i = 0; i < robot_num; i++)
//     {
//         // aStarSearch(&map,robot[i].)
//         if () // 没有到泊口的路
//         {robot[i].status = ROBOT_STUCK;}
//     }
// }



const int robot_num = 10;
Robot robot[robot_num];

// void robotStateInit()
// {
//     for (int i = 0; i < robot_num; i++)
//     {
//         // aStarSearch(&map,robot[i].)
//         if () // 没有到泊口的路
//         {robot[i].status = ROBOT_STUCK;}
//     }
// }

extern numofgds;
extern map;

int isGoodsGrid(Map *goodsmap, Point pos){
    if(pos.x < 0 || pos.x > 200 || pos.y < 0 || pos.y > 200){
        return 0;
    }
    else{
        if(goodsmap->data[pos.x][pos.y] != NULL){
            return 1;
        }
    }
}

// int isGoodsExists(Point* gdsloc, Point gds){
//     while(gdsloc++ != NULL){
//         if(gdsloc == gds){
//             return 0;
//         }
//     }
//     return 1;
// }

LinkList* searchGoods(Map *goodsmap, Robot rob){
    Point curgrid;
    Point goodsloca[121] = {0};//11*11
    int n = 0;//搜索到的货物个数

    int disofgds[121];
    Point temp;
    Point finalgdsloca[3];

    LinkList* temppath[3];
    LinkList* tempph;
    LinkList* finalpath = (LinkList *) malloc(sizeof(LinkList));

    int numofph = 0;
    float valofudis[3];

    for(int i = -5; i < 5; i++){
        for(int j = -5; j < 5; j++){
            curgrid.x = rob.pos.x + i;
            curgrid.y = rob.pos.y + j;
            if(isGoodsGrid(goodsmap, curgrid)){
                goodsloca[n++] = curgrid;
            }
        }
    }
    if(n < 3){
        while(goodsmap){
        }
        int exflag = 0;
        Point rangds;
        for(n; n <= 3; ){
            rangds = goodsmap[rand() % numofgds];
            for(int j=0; j < n; j++){
                if(goodsloca[j].x == rangds.x && goodsloca[j].y == rangds.y)
                    exflag = 1;
                    break;
            }
            if(exflag){
                exflag = 0;
            }
            else{
                goodsloca[n++] = rangds;
            }
            
        }
    }
    for(int i=0; i < n; i++){
        disofgds[i] = abs(rob.pos.x - goodsloca[i].x) + abs(rob.pos.y - goodsloca[i].y);
    }
    for (int i=0; i < n; i++){
        for (int j=0; j < n - 1 - i; j++){
            if (disofgds[j] > disofgds[j + 1]) {
                    temp = goodsloca[j];
                    goodsloca[j] = goodsloca[j + 1];
                    goodsloca[j + 1] = temp;
            }
        }
    }
    for(int i=0; i < 3; i++){
        finalgdsloca[i] = goodsloca[i];
        temppath[i] = aStarSearch(map, rob.pos, finalgdsloca[i]);//获取最新函数定义
        while(temppath[i]->next != NULL){
            temppath[i] = temppath[i]->next;
            numofph++;
        }
        valofudis[i] = valodgs[i] / numofph;//如何保存货物价值 与位置关联起来
    }
    for (int i=0; i < 3; i++){
        for (int j=0; j < 3 - 1 - i; j++){
            if (valofudis[j] > valofudis[j + 1]) {
                    tempph = temppath[j];
                    temppath[j] = temppath[j + 1];
                    temppath[j + 1] = tempph;
            }
        }
    }
    return finalpath = temppath[3];
}

int* pathToDirection(LinkList* path){
    LinkList* temp;
    int *direction;
    temp = path->next;
    while(temp->next != NULL){
        temp = temp->next;
        path = path->next;
        if(temp->grid.loc.x > path->grid.loc.x){
            *direction++ = MOVE_DOWN;
        }
        else if(temp->grid.loc.x < path->grid.loc.x){
            *direction++ = MOVE_UP;
        }
        else if(temp->grid.loc.y > path->grid.loc.y){
            *direction++ = MOVE_RIGHT;
        }
        else if(temp->grid.loc.y < path->grid.loc.y){
            *direction++ = MOVE_LEFT;
        }
    }
*direction = NULL;
    return direction;
}
#include "Robot.h"

const int robot_num = 10;
Robot robot[robot_num];
Map *goodsmap;

#define ROBOT_STUCK -1//困住
#define FREE 0 //空闲
#define ROBOT_GETTING 1//取货
#define ROBOT_SENDING 2//送货
#define ROBOT_CRASHING 3//碰撞
#define ROBOT_VOIDING 4//避让

//carry：0表示未携带物品；stun:0表示恢复状态(晕眩)
void robotstatusupdate(int carry,int stun ,Robot *robot)//机器人状态处理函数
{
    if (carry == 0 && robot->current_status != ROBOT_CRASHING && robot->current_status != ROBOT_STUCK) // 当前状态眩晕
    {
        robot->tempstatus = robot->current_status;
        robot->current_status=ROBOT_CRASHING;
        robot->next_status=ROBOT_CRASHING;
    }
    if (carry != 0 && robot->current_status == ROBOT_CRASHING ) // 上一个状态眩晕
    {
        robot->current_status=robot->tempstatus;
    }
    if(carry==1 && stun==1)
    {robot->current_status=ROBOT_SENDING;}
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
extern Berth berth[];

int isGoodsGrid(Point pos){
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

LinkList* searchGoods(Robot rob){
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
            if(isGoodsGrid(curgrid)){
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
        valofudis[i] = goodsmap->data[goodsloca[i].x][goodsloca[i].y] / numofph;
        numofph = 0;
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
    return finalpath = temppath[2];
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


LinkList* sendGoods(Berth* berths, Robot rob){
=======
LinkList* FindPathBerth(Berth berths[], int num, Robot rob){//返回机器人到泊口的路径
>>>>>>> Stashed changes
    int disofber[10];
    Berth temp;
    LinkList* berthph[3], *tempber;
    int numofph = 0;
    int valperdisofberth[3];
    LinkList* finalberth = (LinkList *) malloc(sizeof(LinkList));

    for(int i=0; i <10; i++){
        disofber[i] = abs(berths[i].pos.x - rob.pos.x) + abs(berths[i].pos.y - rob.pos.y);
    }
    for (int i=0; i < 3; i++){
        for (int j=0; j < 3 - 1 - i; j++){
            if (disofber[j] > disofber[j + 1]) {
                    temp = berths[j];
                    berths[j] = berths[j + 1];
                    berths[j + 1] = temp;
            }
        }
    }
    for(int i=0; i < 3; i++){
        berthph[i] = aStarSearch(map, rob.pos, berths[i].pos);
        while(berthph[i]->next != NULL){
            berthph[i] = berthph[i]->next;
            numofph++;
        }
        valperdisofberth[i] = PATH_FACTOR*numofph + LOADING_FACTOR*berths[i].loading_speed + TRANS_FACTOR*berths[i].transport_time;
        numofph = 0;
    }
    for (int i=0; i < 3; i++){
        for (int j=0; j < 3 - 1 - i; j++){
            if (valperdisofberth[j] > valperdisofberth[j + 1]) {
                    tempber = berthph[j];
                    berthph[j] = berthph[j + 1];
                    berthph[j + 1] = tempber;
            }
        }
    }
    return  finalberth = berthph[2];
}

void robotGetGoodsPrint(Robot rob[], int num){
    for(int i=0; i < num; i++){
        LinkList* path, *nextpath;
        path = searchGoods(rob[i]);
        nextpath = path->next;

        if(nextpath->next != NULL && rob[i].current_status == ROBOT_GETTING){
            updateRobotDirect(&rob[i], path);
            printf("move %d %d\n", i, rob->direct);
        }
        if(nextpath->next != NULL && rob[i].current_status == ROBOT_GETTING){
            printf("get %d\n", i);
        }
    }
}

void robotSendGoodsPrint(Robot rob[], int num){
    for(int i=0; i < num; i++){
        LinkList* path, *nextpath;
        path = sendGoods(berth, rob[i]);
        nextpath = path->next;

        if(nextpath->next != NULL && rob[i].current_status == ROBOT_SENDING){
            updateRobotDirect(&rob[i], path);
            printf("move %d %d\n", i, rob->direct);
        }
        if(nextpath->next != NULL && rob[i].current_status == ROBOT_SENDING){
            printf("pull %d\n", i);
        }       
    }
}
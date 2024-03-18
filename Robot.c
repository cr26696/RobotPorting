#include "Robot.h"

const int num = 10;
Robot robot[num];
Map *goodsmap;

// #define STUCK -1//困住// 已更换为枚举变量在 robot.h中
// #define FREE 0 //空闲
// #define GETTING 1//取货
// #define SENDING 2//送货
// #define CRASHING 3//碰撞
// #define VOIDING 4//避让

/*状态机分状态的转移维护
以及根据状态进行活动
*/
//carry：0表示未携带物品；stun:0表示恢复状态(晕眩)

const int num = 10;
Robot robot[num];


extern numofgds;
extern map;
extern Berth berth[];

//机器人状态处理函数
void robotstatusupdate(int carry,int stun ,Robot *robot)
{
    if (carry == 0 && robot->current_status != CRASHING && robot->current_status != STUCK) // 当前状态眩晕
    {
        robot->tempstatus = robot->current_status;
        robot->current_status=CRASHING;
        robot->next_status=CRASHING;
    }
    if (carry != 0 && robot->current_status == CRASHING ) // 上一个状态眩晕
    {
        robot->current_status=robot->tempstatus;
    }
    if(carry==1 && stun==1)
    {robot->current_status=SENDING;}
}
//判断某点是否为货物 不在main中调用
int isGoodsGrid(Point pos){
    if(pos.x < 0 || pos.x > 200 || pos.y < 0 || pos.y > 200){
        //界外
        return 0;
    }
    else{
        if(goodsmap->data[pos.x][pos.y] != '0'){
            //货物非空 不为'0'
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

//根据计算返回可能是目前去往货物最优的路径 不在main中调用
LinkList* findPathToGoods(Robot rob){
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
//将路径转为direction （int指针 不在main中调用
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

//返回机器人到泊口的路径 不在main中调用
LinkList* findPathToBerth(Berth *berths,  Robot rob){
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

//将路径转化为机器人控制，获取货物 ???之后将这个函数拆分开 num为路径长？调用函数就确定中途不会被打断？
void robotsGetGoodsPrint(Robot rob[], int num){
    for(int i=0; i < num; i++){
        LinkList* path, *nextpath;
        path = findPathToGoods(rob[i]);
        nextpath = path->next;

        if(nextpath->next != NULL && rob[i].current_status == GETTING){
            updateRobotDirect(&rob[i], path);
            printf("move %d %d\n", i, rob->direct);
        }
        if(nextpath->next != NULL && rob[i].current_status == GETTING){
            printf("get %d\n", i);
        }
    }
}
//控制单个机器人取货并进行控制台输出
void robotGetGoodsPrint(Robot *pRob, int id){
    LinkList* path, *nextpath;
    path = findPathToGoods(*pRob);
    nextpath = path->next;

    if(nextpath->next != NULL && pRob->current_status == GETTING){
        updateRobotDirect(pRob, path);
        printf("move %d %d\n", id, pRob->direct);
    }
    if(nextpath->next != NULL && pRob->current_status == GETTING){
        printf("get %d\n", id);
        pRob->next_status = SENDING;
    }
}
//将路径转化为机器人控制，运送货物 ???之后将这个函数拆分开 num为路径长？
void robotsSendGoodsPrint(Robot rob[], int num){
    for(int i=0; i < num; i++){
        LinkList* path, *nextpath;
        path = findPathToBerth(berth, rob[i]);
        nextpath = path->next;

        if(nextpath->next != NULL && rob[i].current_status == SENDING){
            updateRobotDirect(&rob[i], path);
            printf("move %d %d\n", i, rob->direct);
        }
        if(nextpath->next != NULL && rob[i].current_status == SENDING){
            printf("pull %d\n", i);
        }
    }
}
//控制单个机器人送货并进行控制台输出
void robotSendGoodsPrint(Robot *pRob, int id){
    LinkList* path, *nextpath;
    path = findPathToBerth(berth, *pRob);
    nextpath = path->next;

    if(nextpath->next != NULL && pRob->current_status == SENDING){
        updateRobotDirect(pRob, path);
        printf("move %d %d\n", id, pRob->direct);
    }
    if(nextpath->next != NULL && pRob->current_status == SENDING){
        printf("pull %d\n", id);
        pRob->next_status = SENDING;
    }
}
//机器人避让，未完成
int judgeCoincidentGrids(Robot* rob){
    for(int i=0; i < 10; i++){
        if(rob[i].current_status != VOIDING){

        }

    }
}

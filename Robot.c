#include "Robot.h"

// #define num 10
// Robot robot[num];

Map *goodsmap;
LinkParcel* aLLParcelList;
LinkParcel* lockedParcelList;
/**************************************************/


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

extern int numofgds;
extern Map map;
extern Berth berth[];
extern Map ParcelMap;

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
int isParcelGrid(Parcel pos){
	if(pos.loc.x < 0 || pos.loc.x > 200 || pos.loc.y < 0 || pos.loc.y > 200){
		//界外
	}
	else{
		if(goodsmap->data[pos.loc.x][pos.loc.y] != '0'){
			//货物非空 不为'0'
			return 1;
		}
	}
	return 0;
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
LinkList* findPathToGoods(Robot rob, Map MapOfParcels){
	Parcel curgrid;
	Parcel tempparcelarry[120] = {0};//11*11 - 1 减去机器人所在位置???机器人要找的货物列表只存坐标
	int n = 0;//附近货物个数

	int disofgds[120];//11*11 - 1 减去机器人所在位置
	Parcel temp;
	Parcel finalgdsloca[3];

	Parcel tempparcel;
	LinkParcel* templist;

	LinkList* temppath[3];
	LinkList* tempph;
	LinkList* finalpath;
	LinkParcel* nearParcels;

	int numofph = 0;
	float valofudis[3];

	for(int i = -5; i < 5; i++){//在机器人附近的格子搜索
		for(int j = -5; j < 5; j++){
			curgrid.loc.x = rob.pos.x + i;
			curgrid.loc.y = rob.pos.y + j;
			if(MapOfParcels.data[curgrid.loc.x][curgrid.loc.y]!='0'){
				tempparcel.loc.x = curgrid.loc.x;
				tempparcel.loc.y = curgrid.loc.y;
				LinkInsert_ByIndex_Parcel(nearParcels, 1, tempparcel);///之后换用数组存Point类型更好
				//goodsloca[n++] = curgrid;
			}
		}
	}
	n = LinkGetLen_Parcel(nearParcels);
	if(n < 3){
		int exflag = 0;//是否和之前的周围货物重复标志<-----看不懂
		Parcel rangds;
		for(n; n <= 3; ){
			rangds = LinksearchObj_ByPos_Parcel(aLLParcelList, rand() % LinkGetLen_Parcel(aLLParcelList));
			//rangds.x = goodsmap[rand() % numofgds];
			templist = nearParcels;
			while(templist->next != NULL){
				templist = templist->next;
				if(templist->parcel.loc.x == rangds.loc.x && templist->parcel.loc.y == rangds.loc.y){
					exflag = 1;
					break;
				}
			}
			if(exflag){
				exflag = 0;
			}
			else{
				LinkInsert_ByIndex_Parcel(nearParcels, 1, rangds);
				n++;
			}
		}
	}

	templist = nearParcels;
	while(templist->next != NULL){//算机器人到物品的折线距离
		int i = 0;
		templist = templist->next;
		disofgds[i++] = abs(rob.pos.x - templist->parcel.loc.x) + abs(rob.pos.y - templist->parcel.loc.y);
	}
	n = LinkGetLen_Parcel(nearParcels);//更新需要被计算货物数量

	templist = nearParcels;
	while(templist->next != NULL){//将节点存入数组便于排序 或请写一个链表排序
		int i = 0;
		templist = templist->next;
		tempparcelarry[i++] = templist->parcel;
	}
	for (int i=0; i < n - 1; i++){//根据估计出来的粗略距离，对货物数进行排序，距离小的排前面
		for (int j=0; j < n - 1 - i; j++){
			if (disofgds[j] > disofgds[j + 1]) {
					temp = tempparcelarry[j];
					tempparcelarry[j] = tempparcelarry[j + 1];
					tempparcelarry[j + 1] = temp;
			}
		}
	}
	for(int i=0; i < 3; i++){
		Point temppoint;
		finalgdsloca[i] = tempparcelarry[i];//取出三个待选货物
		temppoint = finalgdsloca[i].loc;//aStarSearch()中要传入Point类型 需要temppoint保存 或请修改aStarSearch()形参
		temppath[i] = aStarSearch(&map, rob.pos, temppoint);//根据A*算法计算路径长度
		while(temppath[i]->next != NULL){//???没有考虑当前机器人能不能到三个货物的情况，<----没有
			temppath[i] = temppath[i]->next;
			numofph++;
		}
		valofudis[i] = goodsmap->data[tempparcelarry[i].loc.x][tempparcelarry[i].loc.y] / numofph;//单位格价值
		numofph = 0;
	}
	for (int i=0; i < 3 - 1; i++){//3选一最大单位价值 放在temppath[2]
		for (int j=0; j < 3 - 1 - i; j++){
			if (valofudis[j] > valofudis[j + 1]) {
					tempph = temppath[j];
					temppath[j] = temppath[j + 1];
					temppath[j + 1] = tempph;
			}
		}
	}
	finalpath = temppath[2];//???2?  <-------最大下标为2
	deleteLink_Grid(temppath[0]);
	deleteLink_Grid(temppath[1]);
	return finalpath;
}
//将路径转为direction （int指针 不在main中调用,出错返回-1
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
	*direction = -1;
	return direction;
}

//返回机器人到泊口的路径 不在main中调用
LinkList* findPathToBerth(Berth *berths,  Robot rob){
	int disofber[10];
	Berth temp;
	LinkList* berthph[3], *tempber;
	int numofph = 0;
	int valperdisofberth[3];
	LinkList* finalberth;

	for(int i=0; i <10; i++){
		disofber[i] = abs(berths[i].pos.x - rob.pos.x) + abs(berths[i].pos.y - rob.pos.y);//计算机器人到泊口的折线距离
	}
	for (int i=0; i < 10; i++){//按照disofber[]离泊口步数排序berths[]，粗略距离
		for (int j=0; j < 10 - 1 - i; j++){
			if (disofber[j] > disofber[j + 1]) {
					temp = berths[j];
					berths[j] = berths[j + 1];
					berths[j + 1] = temp;
			}
		}
	}
	for(int i=0; i < 3; i++){//上一步排序完成取前三 计算真实步数
		berthph[i] = aStarSearch(&map, rob.pos, berths[i].pos);
		while(berthph[i]->next != NULL){
			berthph[i] = berthph[i]->next;
			numofph++;
		}
		/*计算泊口价值 */
		valperdisofberth[i] = PATH_FACTOR*numofph + LOADING_FACTOR*berths[i].loading_speed + TRANS_FACTOR*berths[i].transport_time;
		numofph = 0;
	}
	for (int i=0; i < 3; i++){//三选一最近泊口路径 存于berthph[2]
		for (int j=0; j < 3 - 1 - i; j++){
			if (valperdisofberth[j] > valperdisofberth[j + 1]) {
					tempber = berthph[j];
					berthph[j] = berthph[j + 1];
					berthph[j + 1] = tempber;
			}
		}
	}
	finalberth = berthph[2];
	deleteLink_Grid(berthph[0]);
	deleteLink_Grid(berthph[1]);
	return finalberth;
}

//将路径转化为机器人控制，获取货物 ???之后将这个函数拆分开
void robotsGetGoodsPrint(Robot rob[], int num){
	for(int i=0; i < num; i++){
		LinkList* path, *nextpath;
		path = findPathToGoods(rob[i], ParcelMap);
		nextpath = path->next;

		if(nextpath->next != NULL && rob[i].current_status == GETTING){
			updateRobotDirect(&rob[i], path);
			printf("move %d %d\n", i, rob->direct);
		}
		if(nextpath->next != NULL && rob[i].current_status == GETTING){
			printf("get %d\n", i);
		}
		deleteLink_Grid(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
	}
}
//控制单个机器人取货并进行控制台输出
void robotGetGoodsPrint(Robot *pRob, int id){
	LinkList* path, *nextpath;
	path = findPathToGoods(*pRob,ParcelMap);
	nextpath = path->next;

	if(nextpath->next != NULL && pRob->current_status == GETTING){
		updateRobotDirect(pRob, path);
		printf("move %d %d\n", id, pRob->direct);
	}
	if(nextpath->next != NULL && pRob->current_status == GETTING){
		printf("get %d\n", id);
		pRob->next_status = SENDING;
	}
	deleteLink_Grid(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
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
		deleteLink_Grid(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
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
	deleteLink_Grid(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
}
//机器人避让，未完成
// int judgeCoincidentGrids(Robot* rob){
//     for(int i=0; i < 10; i++){
//         if(rob[i].current_status != VOIDING){

//         }

//     }
// }

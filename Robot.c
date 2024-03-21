#include "Robot.h"

extern Map map;
extern Berth berth[];
extern Map parcelMap;
extern Grid gridMap[][200];

extern int numofgds;
extern LinkParcel LinkParcels;
extern LinkParcel LockedParcels;

//机器人状态处理函数 处理判题器输入
void robotstatusupdate(int carry,int awake ,Robot *robot)
{
	if (!awake) // 传入眩晕
	{
		//刚晕
		if(robot->current_status!=CRASHING){
			robot->tempstatus = robot->current_status;
			robot->current_status=CRASHING;
			robot->next_status=CRASHING;
		}
	}else{//传入清醒
		if(robot->current_status == IDLE){//闲着 该干活了
			robot->current_status = GETTING;
			robot->next_status = GETTING;//这帧和下帧应该要进行之前的工作
		}
		else if(robot->current_status == CRASHING){//没醒 给喊醒
			robot->current_status = robot->tempstatus;
			robot->next_status = robot->tempstatus;//这帧和下帧应该要进行之前的工作
		}//else 还在继续晕
		if(carry){//传入清醒 且传入拿货
			if(robot->current_status == GETTING){//捡到货了家人们
				robot->current_status = SENDING;
				robot->current_status = SENDING;
			}
		}else{//传入清醒 且传入没在拿货
				if(robot->current_status == SENDING){//没捡到货就想送货？ 如捡
					robot->current_status = GETTING;
					robot->current_status = GETTING;
				}
			}
	}
	// if(carry==1 && awake==1)
	// {robot->current_status=SENDING;}
}
//判断某点是否为货物 不在main中调用
int isParcelGrid(Parcel pos){
	if(pos.loc.x < 0 || pos.loc.x > 200 || pos.loc.y < 0 || pos.loc.y > 200){
		//界外
	}
	else{
		if(parcelMap.data[pos.loc.x][pos.loc.y] != '0'){
			//货物非空 不为'0'
			return 1;
		}
	}
	return 0;
}

//根据计算返回可能是目前去往货物最优的路径 不在main中调用
LinkPath* findPathToGoods(Robot rob, Map MapOfParcels){
	Parcel curgrid;
	Parcel tempparcelarry[120] = {0};//11*11 - 1 减去机器人所在位置???机器人要找的货物列表只存坐标
	int n = 0;//附近货物个数

	int disofgds[120]={0};//11*11 - 1 减去机器人所在位置
	Parcel temp;
	Parcel finalgdsloca[3];

	Parcel tempparcel;
	LinkParcel* templist;

	LinkPath* temppath[3];
	LinkPath* tempph;
	LinkPath* finalpath;
	LinkParcel* nearParcels = LinkInit_Parcel(nearParcels);

	int numofph = 0;
	float valofudis[3];

	for(int i = -5; i < 5; i++){//在机器人附近的格子搜索
		for(int j = -5; j < 5; j++){
			curgrid.loc.x = rob.pos.x + i;
			curgrid.loc.y = rob.pos.y + j;
			if(MapOfParcels.data[curgrid.loc.x][curgrid.loc.y]!=0){
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
		for(n; n < 3;){
			rangds = LinksearchObj_ByPos_Parcel(&LinkParcels, rand() % numofgds);
			//rangds.x = goodsmap[rand() % numofgds];
			templist = nearParcels;
			while(templist->next != NULL){//遍历判断随机货物是否与附近货物重复
				templist = templist->next;
				if(isSamePosition(templist->parcel.loc,rangds.loc)){
					exflag = 1;//重复
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

	templist = nearParcels->next;//现在temp near Link 包含随机+附近的货物了
	for(int i=0;!(templist == NULL);templist = templist->next){//算机器人到物品的折线距离
		disofgds[i++] = getDistance_Manhattan(rob.pos,templist->parcel.loc);
	}
	n = LinkGetLen_Parcel(nearParcels);//更新需要被计算货物数量

	templist = nearParcels->next;
	for(int i=0;!(templist == NULL);templist = templist->next){//将节点存入数组便于排序 或请写一个链表排序
		tempparcelarry[i++] = templist->parcel;
	}//tempParcelarray赋值？
	for (int i=0; i < n - 1; i++){//根据估计出来的粗略距离，对货物数进行排序，距离小的排前面
		for (int j=0,t; j < n - 1 - i; j++){
			if (disofgds[j] > disofgds[j + 1]) {
					t = disofgds[j];
					disofgds[j] = disofgds[j + 1];
					disofgds[j+1] = t;
					temp = tempparcelarry[j];
					tempparcelarry[j] = tempparcelarry[j + 1];
					tempparcelarry[j + 1] = temp;
			}
		}
	}
	for(int i=0; i < 3; i++){
		Point temppoint;
		finalgdsloca[i] = tempparcelarry[i];//取出三个待选货物
		temppoint = finalgdsloca[i].loc;//
		temppath[i] = aStarSearch(&map, rob.pos, temppoint);//根据A*算法计算路径长度
		numofph = linkGetLen_Path(temppath[i]);

		valofudis[i] = parcelMap.data[tempparcelarry[i].loc.x][tempparcelarry[i].loc.y] / (float)numofph;//单位格价值
		numofph = 0;
	}
	if(valofudis[0]>valofudis[1]){
		if(valofudis[0]>valofudis[2]){ //0 最好
			finalpath = temppath[0];
			linkDelete_Path(temppath[1]);
			linkDelete_Path(temppath[2]);
		}else {//2 最好
			finalpath = temppath[2];
			linkDelete_Path(temppath[0]);
			linkDelete_Path(temppath[1]);
		}
	}else if(valofudis[1]>valofudis[2]){//1最好
		finalpath = temppath[1];
		linkDelete_Path(temppath[0]);
		linkDelete_Path(temppath[2]);
	}

	return finalpath;
}
// //将路径转为direction （int指针 不在main中调用,出错返回-1   <-----不用 直接用geometry.c
// int* pathToDirection(LinkPath* path){
// 	LinkPath* temp;
// 	int *direction;
// 	temp = path->next;
// 	while(temp->next != NULL){
// 		temp = temp->next;
// 		path = path->next;
// 		if(temp->grid.loc.x > path->grid.loc.x){
// 			*direction++ = MOVE_DOWN;
// 		}
// 		else if(temp->grid.loc.x < path->grid.loc.x){
// 			*direction++ = MOVE_UP;
// 		}
// 		else if(temp->grid.loc.y > path->grid.loc.y){
// 			*direction++ = MOVE_RIGHT;
// 		}
// 		else if(temp->grid.loc.y < path->grid.loc.y){
// 			*direction++ = MOVE_LEFT;
// 		}
// 	}
// 	*direction = -1;
// 	return direction;
// }

//返回机器人到泊口的路径 不在main中调用
LinkPath* findPathToBerth(Berth *berths,  Robot rob){
	int disofber[10];
	Berth temp;
	LinkPath* berthph[3], *tempber;
	int numofph = 0;
	int valperdisofberth[3];
	LinkPath* finalberth;

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
	linkDelete_Path(berthph[0]);
	linkDelete_Path(berthph[1]);
	return finalberth;
}

//将路径转化为机器人控制，获取货物 ???之后将这个函数拆分开
void robotsGetGoodsPrint(Robot rob[], int num){
	for(int i=0; i < num; i++){
		LinkPath* path, *nextpath;
		path = findPathToGoods(rob[i], parcelMap);
		nextpath = path->next;

		if(nextpath->next != NULL && rob[i].current_status == GETTING){
			updateRobotDirect(&rob[i], path);
			printf("move %d %d\n", i, rob->direct);
		}
		if(nextpath->next != NULL && rob[i].current_status == GETTING){
			printf("get %d\n", i);
		}
		linkDelete_Path(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
	}
}
//控制单个机器人取货并进行控制台输出
void robotGetGoodsPrint(Robot *pRob, int id){
	LinkPath* path;
	path = findPathToGoods(*pRob,parcelMap)->next;//path直接跳过表头，从内容结点开始（为机器人当前位置）

	if(pRob->current_status == GETTING){
		updateRobotDirect(pRob, path);
		printf("move %d %d\n", id, pRob->direct);
	}
	if(path->next->next == NULL && pRob->current_status == GETTING){//当前节点为机器人目前点，下结点为下步点，下步点无后继==终点
		printf("get %d\n", id);
		pRob->next_status = SENDING;
	}
	linkDelete_Path(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
}
//将路径转化为机器人控制，运送货物 ???之后将这个函数拆分开 num为路径长？
void robotsSendGoodsPrint(Robot rob[], int num){
	for(int i=0; i < num; i++){
		LinkPath* path, *nextpath;
		path = findPathToBerth(berth, rob[i]);
		nextpath = path->next;

		if(nextpath->next != NULL && rob[i].current_status == SENDING){
			updateRobotDirect(&rob[i], path);
			printf("move %d %d\n", i, rob->direct);
		}
		if(nextpath->next != NULL && rob[i].current_status == SENDING){
			printf("pull %d\n", i);
		}
		linkDelete_Path(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
	}
}
//控制单个机器人送货并进行控制台输出
void robotSendGoodsPrint(Robot *pRob, int id){
	LinkPath* path, *nextpath;
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
	linkDelete_Path(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
}

//机器人避让，未完成
/*
int idofrob 机器人编号
return ：1避让 0不避让
*/
void judgeCoincidentGrids(Robot* rob, LinkPath *robotpaths){//机器人编号请使用0-9
	Point robpos[20] = {0};
	int index = 0;//robpos[]中元素个数
	Point temppos;
	for(int i=0; i < 2; i++){//前十格记录机器人当前位置
		robpos[i] = rob->pos;
		index++;
	}
	for(int i=0; i < 10; i++){
		int j = index;
		while(j--){
			if(robotpaths[i].pos.x == robpos[j].x && robotpaths[i].pos.y == robpos[j].y){
				rob->next_status = VOIDING;//与robpos[]中坐标相同，改变机器人状态
			}
			else{
				robpos[index++] = robotpaths[i].pos;//未与robpos[]中元素坐标相同，记录进robpos[]中
			}
		}
	}
}
//void judgeCoincidentGrids(Robot* rob, LinkPath *robotpaths){//机器人编号请使用0-9
    // static LinkPath temprobotpaths[10] = {0};

    // // for(int i=0; i < 10; i++){
    // //     if(temprobotpaths[0].grid.loc.x != pathsofrobot[0].grid.loc.x){//传入新path时重新赋值
    // //             temprobotpaths[i] = pathsofrobot[i];
    // //             temprobotpaths[i] = *temprobotpaths[i].next;
    // //     }
    // // }

    // if(rob[idofrob].current_status != VOIDING){
    //     for(int i=0; i < 10; i++){
    //         if(i != idofrob){
    //             if(pathsofrobot[i].next == NULL /*|| rob[i].current_status != */ ){//其他机器人没有下一步了 或<------需要添加其他条件
    //                 break;
    //             }
    //             /*自身下一步与别人下一步是否重合
    //               自身下一步与别人当前是否重合*/
    //             else if((pathsofrobot[idofrob].next->grid.loc.x == pathsofrobot[i].next->grid.loc.x && pathsofrobot[idofrob].grid.loc.y == pathsofrobot[i].next->grid.loc.y) ||
    //                     (pathsofrobot[idofrob].next->grid.loc.x == pathsofrobot[i].grid.loc.x && pathsofrobot[idofrob].next->grid.loc.y == pathsofrobot[i].grid.loc.y)){
    //                     rob[idofrob].current_status = VOIDING;
    //                     return 1;
    //             }
    //         }
    //     }
    // }
    // else{
    //     return 0;
    // }
	// return 0;
//}


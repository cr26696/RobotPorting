#include "Robot.h"

extern Map map;
extern Berth berth[];
extern Parcel parcelMap[200][200];
extern Grid gridMap[][200]; 

extern int toAvoidLen;
extern Point toAvoid[20];
extern int numofgds;
extern LinkParcel LinkParcels;
extern LinkParcel LockedParcels;

//机器人状态处理函数 处理判题器输入与当前状态不一样问题
void robotUpdate_sysInput(int carry,int awake ,Robot *pRob)
{
	if (!awake) // 传入眩晕
	{
		if(pRob->current_status!=CRASHING){//之前没晕
			pRob->tempstatus = pRob->current_status;
			pRob->current_status=CRASHING;
			pRob->next_status=CRASHING;
		}
	}else{//传入清醒
		// if(pRob->current_status == IDLE){//闲着 该干活了
		// 	pRob->current_status = SearchParcel;
		// 	pRob->next_status = SearchParcel;//这帧和下帧应该要进行之前的工作
		// }
		// else 
		if(pRob->current_status == CRASHING){//没醒 给喊醒
			pRob->current_status = pRob->tempstatus;
			// pRob->next_status = pRob->tempstatus;//这帧和下帧应该要进行之前的工作
		}//else 还在继续晕
	
		if(carry){//传入清醒 且传入拿货
			if(pRob->current_status ==SearchBerth){//确定取到货物
				LinkDelete_ByPoint_Parcel(&LinkParcels,pRob->pos);//从倒计时链表中删除
				parcelMap[pRob->pos.x][pRob->pos.y].value = 0;//从二维表中删除
			}
			else if(pRob->current_status == GETTING){//捡到货了家人们
				pRob->current_status = SearchBerth;
			}
		}else{//传入清醒 且传入没在拿货
				if(pRob->current_status == SENDING){//没捡到货就想送货？ 如捡
					pRob->current_status = SearchParcel;
					pRob->reLocCount = 0;
				}
		}
	}
	if(pRob->curPath!=NULL){//链表有空结点表头
		if(pRob->curPath->next!=NULL){//链表第一个内容节点不为空(上步走了-上步点) （上步没走-当前点）
			if(pRob->curPath->next->next!=NULL){//链表第二个内容节点不为空 (上步走了-当前点) （上步没走-下个点
				if(isSamePosition(pRob->pos,pRob->curPath->next->next->pos))
				linkDelete_byPos_Path(pRob->curPath,1); //删除走过的点（上个点）

				//需要free掉已经走完的路径
			}else{//链表第二个内容节点为空

			}
		}
	}
}
//判断某点是否为货物 不在main中调用
// int isParcelGrid(Parcel pos){
// 	if(pos.loc.x < 0 || pos.loc.x > 200 || pos.loc.y < 0 || pos.loc.y > 200){
// 		//界外
// 	}
// 	else{
// 		if(parcelMap.data[pos.loc.x][pos.loc.y] != '0'){
// 			//货物非空 不为'0'
// 			return 1;
// 		}
// 	}
// 	return 0;
// }


//根据计算返回可能是目前去往货物最优的路径 不在main中调用
LinkPath* findPathToGoods(Robot* rob){
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
	//输入机器人坐标 返回合理的搜索范围
	for(int i = -5; i < 5; i++){//在机器人附近的格子搜索
		for(int j = -5; j < 5; j++){
			if(rob->pos.x + i < 0 || rob->pos.y + j < 0 ||
			   rob->pos.x + i > 199 || rob->pos.y + j > 199){
				continue;
			}
			else{
				curgrid.loc.x = rob->pos.x + i;
				curgrid.loc.y = rob->pos.y + j;
				if(!parcelMap[curgrid.loc.x][curgrid.loc.y].locked){
					if(parcelMap[curgrid.loc.x][curgrid.loc.y].value != 0){
					tempparcel.loc.x = curgrid.loc.x;
					tempparcel.loc.y = curgrid.loc.y;
					//parcelMap[curgrid.loc.x][curgrid.loc.y].locked = 1;
					LinkInsert_ByIndex_Parcel(nearParcels, 1, tempparcel);///之后换用数组存Point类型更好
					n++;
					//goodsloca[n++] = curgrid;
					}
				}
			}
		}
	}

	// n = LinkGetLen_Parcel(nearParcels);上面用n++
	if(!n){
		templist = &LinkParcels;
		//int exflag = 0;//是否和之前的周围货物重复标志
		while(templist->next != NULL){
			templist = templist->next;
			if(!parcelMap[templist->parcel.loc.x][templist->parcel.loc.y].locked && parcelMap[templist->parcel.loc.x][templist->parcel.loc.y].value!=0){
				LinkInsert_ByIndex_Parcel(nearParcels, 1, templist->parcel);
				//nearParcels->next = &templist->parcel;
				n++;
				break;
			}
		}
		if(nearParcels->next == NULL){
			rob->next_status = SearchBerth;
			return NULL;
		}
		//Parcel rangds;
		//for(n; n < 3;){
			//rangds.x = goodsmap[rand() % numofgds];
			// templist = nearParcels;
			// while(templist->next != NULL){//遍历判断随机货物是否与附近货物重复
			// 	templist = templist->next;
			// 	if(isSamePosition(templist->parcel.loc,rangds.loc)){
			// 		exflag = 1;//重复
			// 		break;
			// 	}
			// }
			// if(exflag){
			// 	exflag = 0;
			// }
			// else{
			// 	LinkInsert_ByIndex_Parcel(nearParcels, 1, rangds);
			// 	n++;
			// }
		//}
	}

	templist = nearParcels->next;//现在temp near Link 包含随机+附近的货物了
	for(int i=0;!(templist == NULL);templist = templist->next){//算机器人到物品的折线距离
		disofgds[i++] = getDistance_Manhattan(rob->pos,templist->parcel.loc);
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

	for(int i=0; i < n; i++){
		Point temppoint;
		finalgdsloca[i] = tempparcelarry[i];//取出三个待选货物
		temppoint = finalgdsloca[i].loc;//
		temppath[i] = aStarSearch(&map, rob->pos, temppoint);//根据A*算法计算路径长度
		if(!temppath[i]){
				parcelMap[temppoint.x][temppoint.y].value = 0;
				parcelMap[temppoint.x][temppoint.y].locked = 1;
				LinkDelete_ByPoint_Parcel(&LinkParcels,temppoint);
				return NULL;
		}else numofph = linkGetLen_Path(temppath[i]);

		valofudis[i] = parcelMap[tempparcelarry[i].loc.x][tempparcelarry[i].loc.y].value / (float)numofph;//单位格价值
		numofph = 0;
	}

	int bestIndex = 0;//暂存最佳值 //返回最佳路径
	float bestPathValue=valofudis[0];
	for(int i = 0; i < n; i++){
		if(valofudis[i]>bestPathValue){
			bestPathValue = valofudis[i];
			bestIndex = i;
		}
	}
	finalpath = temppath[bestIndex];
	for(int i = 0; i < n; i++){
		if(i==bestIndex)continue;
		if(temppath[i])linkDelete_Path(temppath[i]);
	}
	rob->aim = finalgdsloca[bestIndex].loc;
	parcelMap[rob->aim.x][rob->aim.y].locked = 1;
	return finalpath;
}


//返回机器人到泊口的路径 不在main中调用
LinkPath* findPathToBerth(Berth *berths,  Robot* rob){
	int disofber[10];
	Berth temp;
	LinkPath* berthph[3], *tempber;
	int numofph = 0;
	int valperdisofberth[3];
	LinkPath* finalberth;
	int tempIndex[3];
	int tempVal[3] = {999,999,999};


	for(int i=0;i<10;i++){
		disofber[i] =	getDistance_Manhattan(berths[i].pos,rob->pos);
	}

	tempIndex[0] = 0;

	for(int i=0;i<10;i++){
		if(disofber[i]<tempVal[0]){
			tempVal[0] = disofber[i];
			tempIndex[0] = i;
		}
	}
	
	for(int i=0;i<10;i++){
		if(i==tempIndex[0])continue;
		if(disofber[i]<tempVal[1]){
			tempVal[1] = disofber[i];
			tempIndex[1] = i;
		}
	}
	for(int i=0;i<10;i++){
		if(i==tempIndex[0] ||i==tempIndex[1])continue;
		if(disofber[i]<tempVal[2]){
			tempVal[2] = disofber[i];
			tempIndex[2] = i;
		}
	}//找出前三个最小曼哈顿距离 将序号放在tempIndex[]

	for(int i=0; i < 3; i++){//上一步排序完成取前三 计算真实步数s
		berthph[i] = aStarSearch(&map, rob->pos, getBerthNearPos(berths[tempIndex[i]].pos,rob->pos));
		numofph = linkGetLen_Path(berthph[i]);
		/*计算泊口价值 */
		valperdisofberth[i] = evaluateBerth(berths[tempIndex[i]].loading_speed,0.1,berths[tempIndex[i]].transport_time,0.6,numofph,1);
		// valperdisofberth[i] = PATH_FACTOR*numofph + LOADING_FACTOR*berths[i].loading_speed + TRANS_FACTOR*berths[i].transport_time;
	}
	int bestIndex = 0;//暂存最佳值 //返回最佳路径
	float bestPathValue=valperdisofberth[0];
	for(int i=1;i<3;i++){
		if(valperdisofberth[i]>bestPathValue){
			bestPathValue = valperdisofberth[i];
			bestIndex = i;
		}
	}
	finalberth = berthph[bestIndex];
	for(int i=0;i<3;i++){
		if(i==bestIndex)continue;
		if(berthph[i])linkDelete_Path(berthph[i]);
	}
	rob->aimBerth = tempIndex[bestIndex];
	rob->aim = berths[tempIndex[bestIndex]].pos;
	return finalberth;
}

//
void robotGetParcelPath(Robot* pRob){
	LinkPath* tempPath = findPathToGoods(pRob);
	if(pRob->curPath)linkDelete_Path(pRob->curPath);
	// free(pRob->curPath);
	pRob->curPath = tempPath;
}
void robotGetBerthPath(Robot* pRob){
	LinkPath* tempPath = findPathToBerth(berth,pRob);
	free(pRob->curPath);
	pRob->curPath = tempPath;
}
void robotUpdate_Action(Robot *pRob)
{
	switch (pRob->current_status)
	{
	case IDLE:
		pRob->current_status = SearchParcel;
		pRob->next_status = GETTING;
		pRob->reLocCount = 0;
	break;
	case GETTING:
		pRob->reLocCount++;
		if(isSamePosition(pRob->pos,pRob->aim)){
			pRob->current_status=GET;
			pRob->next_status=SearchBerth;
			break;
		}
		if(isSamePosition(pRob->curPath->next->next->pos,pRob->aim)){//下个点为目标点
			pRob->next_status = GET;
		}else{//不为目标点，尝试重新搜索周围
			if(pRob->reLocCount>TimeLimit){
				pRob->next_status = SearchParcel;
				pRob->reLocCount = 0;
				break;
			}else {}
		}
		pRob->moveDirect = getStepDirect(pRob->curPath->next->pos,pRob->curPath->next->next->pos);//更新机器人行动方向
	break;
	case GET:
		pRob->next_status = SearchBerth;
	break;
	case SENDING:
		if(isSamePosition(pRob->pos,pRob->aim)){
			pRob->current_status=PULL;
			pRob->next_status=SearchParcel;
			break;
		}
		if(isSamePosition(pRob->curPath->next->next->pos,pRob->aim)){
			pRob->next_status = PULL;
		}
		pRob->moveDirect = getStepDirect(pRob->curPath->next->pos,pRob->curPath->next->next->pos);//更新机器人行动
	break;
	case PULL:
		pRob->next_status = SearchParcel;
	break;
	case SearchParcel:
		pRob->next_status = GETTING;
		pRob->reLocCount = 0;
	break;
	case SearchBerth:
		pRob->next_status = SENDING;
	break;
	case VOIDING:pRob->next_status=pRob->tempstatus;
	default:break;
	}
}

void robotAction(Robot* pRob){
	switch (pRob->current_status)
	{
		break;
		case SearchParcel:
			parcelMap[pRob->aim.x][pRob->aim.y].locked = 0;
			robotGetParcelPath(pRob);
			if (pRob->curPath==NULL)pRob->next_status=SearchParcel;
		break;
		case GETTING:
			if(!AvoidPossibleCollide(*pRob)){
				printf("move %d %d\n", pRob->id, pRob->moveDirect);
			}else{
				pRob->tempstatus=pRob->current_status;
				pRob->next_status = VOIDING;
				pRob->current_status = VOIDING;
			}
		break;
		case GET:
			printf("get %d\n", pRob->id);
		break;
		case SearchBerth:
			robotGetBerthPath(pRob);
			if (pRob->curPath==NULL)pRob->next_status=SearchBerth;
		break;
		case SENDING:
			if(!AvoidPossibleCollide(*pRob)){
				printf("move %d %d\n", pRob->id, pRob->moveDirect);
			}else{
				pRob->next_status = pRob->current_status;
				pRob->current_status = VOIDING;
			}
		break;
		case PULL:
			printf("pull %d\n", pRob->id);
			berth[pRob->aimBerth].goodsnum++;//放下货物，泊口货物数++
		break;
		case VOIDING:
			//还没写
		break;
		default:break;
	}
}
// void (Robot *pRob, int id){
// 	LinkPath* path;
// 	path = findPathToGoods(*pRob,parcelMap);
// 	path = path->next;//path直接跳过表头，从内容结点开始（为机器人当前位置）
// 	if(pRob->current_status == GETTING){
// 		updateRobotDirect(pRob, path);
// 		printf("move %d %d\n", id, pRob->moveDirect);
// 	}
// 	if(path->next->next == NULL && pRob->current_status == GETTING){//当前节点为机器人目前点，下结点为下步点，下步点无后继==终点
// 		printf("get %d\n", id);
// 		pRob->next_status = SENDING;
// 	}
// 	linkDelete_Path(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
// }

//控制单个机器人送货并进行控制台输出
// void robotSendGoodsPrint(Robot *pRob, int id){
// 	LinkPath* path, *nextpath;
// 	path = findPathToBerth(berth, *pRob);
// 	nextpath = path->next;

// 	if(nextpath->next != NULL && pRob->current_status == SENDING){
// 		updateRobotDirect(pRob, path);
// 		printf("move %d %d\n", id, pRob->moveDirect);
// 	}
// 	if(nextpath->next != NULL && pRob->current_status == SENDING){
// 		printf("pull %d\n", id);
// 		pRob->next_status = SENDING;
// 	}
// 	linkDelete_Path(path);//现在为了避免溢出，只能在任何新建路径之后调用delete!!!
// }

//机器人避让，未完成
/*
int idofrob 机器人编号
return ：1避让 0不避让
*/
void judgeCoincidentGrids(Robot* rob, LinkPath *robotpaths){//机器人编号请使用0-9
	Point robpos[20] = {0};//使用点数组 存储可能发生碰撞的点
	int index = 0;//robpos[]中元素个数
	Point temppos;
	for(int i=0; i < 10; i++){//前十格记录机器人当前位置
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
int AvoidPossibleCollide(Robot rob){
	int avoidFlag = 0;
	Point nextPos = rob.curPath->next->next->pos;
	for(int i=0;i<toAvoidLen;i++){
		if(isSamePosition(nextPos,toAvoid[i])){avoidFlag = 1;break;}
	}
	if(avoidFlag)return avoidFlag;
	else{
		toAvoid[toAvoidLen].x = nextPos.x;
		toAvoid[toAvoidLen].y = nextPos.y;
		toAvoidLen++;
		return avoidFlag;
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


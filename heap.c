#include "heap.h"

typedef struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} BiNode;

int CreateTree(BiNode** root) {
 
	int val;
	scanf_s("%d", &val);
	if (val <= 0) {
		*root = NULL;
		return 0;
	}
 
	*root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	if (!root) {
		printf("创建失败\n");
	}
 
	if (val > 0) {
		(*root)->val = val;
		CreateTree(&((*root)->left));
		CreateTree(&((*root)->right));
	}
	return 0;
}


//交换
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//将以k为根结点的子树调整为大根堆
void MaxHeadAdjust(int A[], int k, int len){
    A[0] = A[k];                                //将子树根结点暂存在A[0]
    for (int i = 2 * k; i <= len; i *= 2) {     //沿值较大的子节点向下筛选
        if (i < len && A[i] < A[i + 1])         //如果它的左孩子的值小于右孩子的值
            i++;
        if (A[0] >= A[i])                       //如果根结点的值比左右孩子的最大值还要大或相等
            break;
        else {
            A[k] = A[i];                        //交换根结点与左右子孩子中最大值的结点
            k = i;                              //修改k的值，以便继续向下筛选
        }
    }
    A[k] = A[0];                                  //被筛选结点的值放入最终位置
}

//将以k为根结点的子树调整为小根堆
void MinHeadAdjust(int A[], int k, int len){
    A[0] = A[k];                                //将子树根结点暂存在A[0]
    for (int i = 2 * k; i <= len; i *= 2) {     //沿值较大的子节点向下筛选
        if (i < len && A[i] > A[i + 1])         //如果它的左孩子的值大于右孩子的值
            i++;
        if (A[0] <= A[i])                       //如果根结点的值比左右孩子的最小值还要小或相等
            break;
        else {
            A[k] = A[i];                        //交换根结点与左右子孩子中最小值的结点
            k = i;                              //修改k的值，以便继续向下筛选
        }
    }
    A[k] = A[0];                                  //被筛选结点的值放入最终位置
}

//建立大根堆
void BuildMaxHeap(int A[], int len){
    for (int i = len / 2; i > 0; --i) {         //从i=[len/2]~1，反复调整堆
        MaxHeadAdjust(A, i, len);
    }
}

//建立小根堆
void BuildMinHeap(int A[], int len){
    for (int i = len / 2; i > 0; --i) {         //从i=[len/2]~1，反复调整堆
        MinHeadAdjust(A, i, len);
    }
}

//大根堆排序
void MaxHeapSort(int A[], int len){
    BuildMaxHeap(A, len);                       //初始建立大根堆
    for (int i = len; i > 1; --i) {             //len-1趟交换和建堆过程
        swap(&A[i], &A[1]);                 //将对顶元素和堆底元素交换
        MaxHeadAdjust(A, 1, i - 1);      //调整，将剩余的i-1个元素继续整理为大根堆
    }
}

//小根堆排序
void MinHeapSort(int A[], int len){
    BuildMinHeap(A, len);                       //初始建立小根堆
    for (int i = len; i > 1; --i) {             //len-1趟交换和建堆过程
        swap(&A[i], &A[1]);                 //将对顶元素和堆底元素交换
        MinHeadAdjust(A, 1, i - 1);      //调整，将剩余的i-1个元素继续整理为小根堆
    }
}

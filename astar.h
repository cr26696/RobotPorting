#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Pos;//坐标

typedef struct node {
  node* father;
  int G, F, H;
  bool inOpen,inClose;
}node;//节点


Pos AstarPath[400]; 
node openlist[]

int isValid(int row, int col);//越界判断
int calculateHValue(int row, int col, Pos dest)//H值计算函数
void tracePath(Node nodeDetails[][COL], Pos dest)//回溯生成path
void aStarSearch(int grid[][COL], Pair src, Pair dest){

  OPEN = priority queue containing START

CLOSED = empty set

while lowest rank in OPEN is not the GOAL:

  current = remove lowest rank item from OPEN

  add current to CLOSED

  for neighbors of current:

    cost = g(current) + movementcost(current, neighbor)

    if neighbor in OPEN and cost less than g(neighbor):

      remove neighbor from OPEN, because new path is better

    if neighbor in CLOSED and cost less than g(neighbor): **

      remove neighbor from CLOSED

    if neighbor not in OPEN and neighbor not in CLOSED:

      set g(neighbor) to cost

      add neighbor to OPEN

      set priority queue rank to g(neighbor) + h(neighbor)

      set neighbor's parent to current
}

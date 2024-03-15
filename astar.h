#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>

Pos AstarPath[400]; 
node openlist[];

#define value_inf 65535;

typedef struct {
  int x;
  int y;
} Pos;//坐标

typedef struct node {
  node* father;
  int G, F, H;
  int inOpen,inClose;
}node;//节点


Pos AstarPath[400];


int isValid(int row, int col);//越界判断
int calculateHValue(int row, int col, Pos dest);//H值计算函数
void tracePath(Node nodeDetails[][COL], Pos dest);//回溯生成path

// void aStarSearch(int map*, Pos src, Pos dest){
int max_nodes = grid.length * grid[0].length;

  nodeList openList = createList(max_nodes);
  nodeList closeList = createList(max_nodes);

//   OPEN = priority queue containing START

  //OPEN = priority queue containing START
  node startNode;
  startNode.father = *startNode;
  startNode.F = value_inf;
  startNode.G = value_inf;
  startNode.H = value_inf;
  startNode.inOpen = 0;
  startNode.inClose = 0;

  openList.insert(startNode)

//   //CLOSED = empty set

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

void getFdistance(Grid *grid, Goods *goods){
    int hdistance;
    hdistance = abs(grid->x - goods->x) + abs(grid->y - goods->y);
}
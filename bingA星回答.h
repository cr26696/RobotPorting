//
#include <stdio.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

// Creating a shortcut for int, int pair type 坐标类型
typedef struct {
    int first;
    int second;
} Pair;

// 带fgh值的节点
typedef struct {
    Pair parent;
    double f, g, h;
} Node;

// 防止越界
int isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// 计算H(不确定)值函数.
double calculateHValue(int row, int col, Pair dest) {
    // 使用斜线距离
    return ((double)sqrt((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

// 回溯生成path Utility Function to trace the path from the source to destination 
void tracePath(Node nodeDetails[][COL], Pair dest) {
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    Pair path[ROW*COL];//路线，最长为全图坐标格
    int index = 0;//迭代层数
    while (!(nodeDetails[row][col].parent.first == row && nodeDetails[row][col].parent.second == col)) {
        path[index] = (Pair){row, col};
        int temp_row = nodeDetails[row][col].parent.first;
        int temp_col = nodeDetails[row][col].parent.second;
        row = temp_row;
        col = temp_col;
        index++;
    }//迭代寻找目标节点的父节点，直到找到一个节点的父节点是它自己
    //出循环时row col 为起始节点坐标
    path[index] = (Pair){row, col};
    while (index >= 0) {
        printf("-> (%d,%d) ", path[index].first, path[index].second);
        index--;
    }
    return;
}

// 寻路主函数 A Function to find the shortest path between a given source cell to a destination cell
void aStarSearch(int grid[][COL], Pair src, Pair dest) {
    // If the source is out of range
    if (isValid(src.first, src.second) == 0) {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == 0) {
        printf("Destination is invalid\n");
        return;
    }
    //↑ 判断目标、起始点是否越界
    // Either the source or the destination is blocked
    if (grid[src.first][src.second] == 0 || grid[dest.first][dest.second] == 0) {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (src.first == dest.first && src.second == dest.second) {
        printf("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which means that no cell has been included yet
    // This closed list is implemented as a boolean 2D array
    //关闭列表
    int closedList[ROW][COL];
    memset(closedList, 0, sizeof(closedList));

    // 存储所有的节点代价及父节点 Declare a 2D array of structure to hold the details of that cell
    Node nodeDetails[ROW][COL];

    int i, j;
    for (i = 0; i < ROW; i++) {//初始化值为最大
        for (j = 0; j < COL; j++) {
            nodeDetails[i][j].f = FLT_MAX;
            nodeDetails[i][j].g = FLT_MAX;
            nodeDetails[i][j].h = FLT_MAX;
            nodeDetails[i][j].parent.first = -1;
            nodeDetails[i][j].parent.second = -1;
        }
    }

    // 起始节点初始化 Initialising the parameters of the starting node
    i = src.first, j = src.second;
    nodeDetails[i][j].f = 0.0;
    nodeDetails[i][j].g = 0.0;
    nodeDetails[i][j].h = 0.0;
    nodeDetails[i][j].parent.first = i;
    nodeDetails[i][j].parent.second = j;//起始节点父节点为其本身

    /*
    Create an open list having information as-
    <f, <i, j>>
    where f = g + h,
    and i, j are the row and column index of that cell
    Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    This open list is implemented as a set of pair of pair.
    开放列表
    */
    set<Pair> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));//？makepair?

    // 是否找到目标点We set this boolean value as false as initially the destination is not reached.
    int foundDest = 0;

    while (!openList.empty()) {
        Pair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = 1;

        /*
        Generating all the 8 successor of this cell

            N.W   N   N.E
              \   |   /
               \  |  /
            W----Cell----E
                 / | \
               /   |  \
            S.W    S   S.E

        Cell-->Popped Cell (i, j)
        N -->  North       (i-1, j)
        S -->  South       (i+1, j)
        E -->  East        (i, j+1)
        W -->  West           (i, j-1)
        N.E--> North-East  (i-1, j+1)
        N.W--> North-West  (i-1, j-1)
        S.E--> South-East  (i+1, j+1)
        S.W--> South-West  (i+1, j-1)*/

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one
        if (isValid(i-1, j) == 1) {
            // If the destination cell is the same as the current successor
            if (isDestination(i-1, j, dest) == 1) {
                // Set the Parent of the destination cell
                nodeDetails[i-1][j].parent.first = i;
                nodeDetails[i-1][j].parent.second = j;
                printf("The destination cell is found\n");
                tracePath(nodeDetails, dest);
                foundDest = 1;
                return;
            }
            // If the successor is already on the closed list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i-1][j] == 0 && isUnBlocked(grid, i-1, j) == 1) {
                gNew = nodeDetails[i][j].g + 1.0;
                hNew = calculateHValue(i-1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to the open list. Make the current square
                // the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (nodeDetails[i-1][j].f == FLT_MAX || nodeDetails[i-1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i-1, j)));

                    // Update the details of this cell
                    nodeDetails[i-1][j].f = fNew;
                    nodeDetails[i-1][j].g = gNew;
                    nodeDetails[i-1][j].h = hNew;
                    nodeDetails[i-1][j].parent.first = i;
                    nodeDetails[i-1][j].parent.second = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid(i+1, j) == 1) {
            // If the destination cell is the same as the current successor
            if (isDestination(i+1, j, dest) == 1) {
                // Set the Parent of the destination cell
                nodeDetails[i+1][j].parent.first = i;
                nodeDetails[i+1][j].parent.second = j;
                printf("The destination cell is found\n");
                tracePath(nodeDetails, dest);
                foundDest = 1;
                return;
            }
            // If the successor is already on the closed list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i+1][j] == 0 && isUnBlocked(grid, i+1, j) == 1) {
                gNew = nodeDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add
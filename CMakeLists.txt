cmake_minimum_required(VERSION 3.22)

# set the project name
project(CodeCraftSDK)

# add the executable
add_executable(main main.c astar.c Boat.c geometry.c heap.c initAll.c LinkGrid.c LinkParcel.c LinkPath.c moveControl.c Robot.c)
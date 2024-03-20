cmake_minimum_required(VERSION 3.22)

# set the project name
project(RobortPorting)

# add the executable
add_executable(exectable main.c astar.c Boat.c geometry.c initAll.c LinkGrid.c LinkParcel.c LinkPath.c moveControl.c Robot.c)
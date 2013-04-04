cmake_minimum_required(VERSION 2.8)
project(server)

SET( CMAKE_CXX_FLAGS_DEBUG " -O0 -Wall -Werror -g -ggdb")
SET( CMAKE_C_FLAGS_DEBUG " -O0 -Wall -Werror -g -ggdb")
SET( CMAKE_BUILD_TYPE Debug )


#SET(CMAKE_CXX_COMPILER "clang")
SET(CMAKE_CXX_COMPILER "ccache")
SET(CMAKE_CXX_COMPILER_ARG1 "g++")


#SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_C_COMPILER "ccache")
SET(CMAKE_C_COMPILER_ARG1 "gcc")

INCLUDE_DIRECTORIES(
        content
        handler
        ./
)
SET( SRC_LIST 
./main.cpp
./Config.cpp
./SendTask.cpp
./database.cpp
./Evloop.cpp
./Sock.c
./Single.cpp
./ThreadPool.cpp
./RecvTask.cpp 
./handler/HandleCartoon.cpp
./handler/HandleExercise.cpp
./handler/HandleClassRoom.cpp
./handler/HandleSprite.cpp
./handler/HandleBuildHouse.cpp
./handler/HandlePuzzle.cpp
./handler/HandleMessage.cpp
./ProcessManager.cpp
./content/course.cpp
./content/courseitem.cpp
./content/teacher.cpp
./content/room.cpp
./content/grade.cpp
./content/game.cpp
./content/student.cpp
./content/roommanager.cpp
./content/LoginCheck.cpp
)

SET(EXTRA_LIBS 
-lpthread -lrt -lev -lglog -lmysqlcppconn -llua5.2
)

add_executable(server ${SRC_LIST})
target_link_libraries (server ${EXTRA_LIBS})

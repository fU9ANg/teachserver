AUTOMAKE_OPTIONS=gnu
bin_PROGRAMS=server
INCLUDES=-I./handler -I./content

server_LDADD=-lglog -lpthread -llua5.2 -lev -ldl -lrt -lmysqlcppconn
#server_LDFLAGS = -g -Wall -Werror
#server_CFLAGS = -g -Wall -Werror
#server_CPPFLAGS= -g -Wall -Werror
server_SOURCES=./main.cpp ./config.h ./Single.cpp ./QueueT.h ./Evloop.h ./SendTask.h ./ProcessManager.h ./Config.cpp ./Mutex.h ./handler/HandleMessage.cpp ./handler/HandleBuildHouse.cpp ./handler/HandleExercise.cpp ./handler/HandlePuzzle.cpp ./handler/HandleCartoon.cpp ./handler/HandleSprite.cpp ./handler/HandleMessage.h ./handler/HandleClassRoom.cpp ./ThreadPool.h ./twomapT.h ./database.h ./content/teacher.cpp ./content/courseitem.cpp ./content/roommanager.cpp ./content/course.cpp ./content/courseitem.h ./content/student.cpp ./content/room.h ./content/teacher.h ./content/student.h ./content/course.h ./content/game.cpp ./content/grade.h ./content/grade.cpp ./content/LoginCheck.cpp ./content/room.cpp ./content/roommanager.h ./content/LoginCheck.h ./content/game.h ./ThreadPool.cpp ./Sock.h ./database.cpp ./SQL.h ./protocol.h ./Buf.h ./PoolT.h ./Single.h ./task.h ./Evloop.cpp ./RecvTask.cpp ./AtomicT.h ./SendTask.cpp ./ProcessManager.cpp ./Config.h ./RecvTask.h ./Sock.c ./content/makehouse.cpp ./content/puzzle.cpp

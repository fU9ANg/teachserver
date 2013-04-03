AUTOMAKE_OPTIONS= gnu
bin_PROGRAMS= teachserver

INCLUDES= -I./handler -I./content
LIBS= -lpthread -lrt -lev -lglog -L/usr/lib -lmysqlcppconn /usr/lib/liblua.a
AM_LDFLAGS= -g -Wall -Werror
AM_CFLAGS= -g -Wall -Werror
AM_CPPFLAGS= -g -Wall -Werror

teachserver_SOURCES=RecvTask.cpp handler/HandleCartoon.cpp handler/HandleSprite.cpp handler/HandleMessage.cpp handler/HandleClassRoom.cpp handler/HandlePuzzle.cpp handler/HandleBuildHouse.cpp handler/HandleExercise.cpp SendTask.cpp Single.cpp main.cpp Sock.c ThreadPool.cpp content/game.cpp content/teacher.cpp content/roommanager.cpp content/student.cpp content/courseitem.cpp content/course.cpp content/room.cpp content/LoginCheck.cpp content/grade.cpp ProcessManager.cpp Evloop.cpp Config.cpp database.cpp

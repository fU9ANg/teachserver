CPP=ccache g++ 
CC=ccache gcc
CFLAGS=-Wall -Werror -g
LINKS	= -lpthread -lrt -lev -lglog -lmysqlcppconn -llua5.2

OBJS	= ThreadPool.o \
		  content/LoginCheck.o \
          content/student.o \
		  content/room.o \
		  content/grade.o \
          content/course.o \
		  content/courseitem.o \
		  content/roommanager.o \
		  content/teacher.o \
		  content/game.o \
		  handler/HandleBuildHouse.o \
		  handler/HandleClassRoom.o \
		  handler/HandleMessage.o \
		  handler/HandleSprite.o \
		  handler/HandleCartoon.o \
		  handler/HandleExercise.o \
		  handler/HandlePuzzle.o \
		  ProcessManager.o \
		  Single.o \
		  Sock.o \
		  Evloop.o \
		  RecvTask.o \
		  SendTask.o \
		  database.o \
		  Config.o \
		  main.o

EXE=server

VPATH		 = .

INC=-I. -I./content -I./handler

LIB=-L.

all:clean $(EXE)

$(EXE):$(OBJS)
		 $(CPP) $(CFLAGS) $(LIB) $(OBJS) -o $@ $(LINKS)

%.o:%.cpp
		 $(CPP) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.c
		 $(CC)  $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS) 
	rm -rf $(EXE) 
	rm -rf core*
	rm -rf logs
	rm -f .lock

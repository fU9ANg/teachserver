/*
 * room.h
 */

#ifndef _C_ROOM_H
#define _C_ROOM_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

#include "teacher.h"
#include "student.h"
#include "grade.h"
#include "database.h"
#include "SQL.h"
#include "game.h"

#include "course.h"

#include "HandleMessage.h"

class CRoom
{
	typedef map<int, CStudent*> STUDENTMAP;
    typedef list<CCourse*> COURSELIST;
    typedef list<CGame*> GAMELIST;

public:
	 CRoom(int id, string class_name, string white_board);
	~CRoom ();

    //friend bool CHandleMessage::postTeacherToAllStudent (Buf* p, enum CommandType iCommandType);
    friend class CHandleMessage;

    int  get_room_id();
    void set_teacher_fd(int fd);
    void set_teacher_name(string name);
    void set_class_name(string name);
    void set_white_fd(int fd);
    void add_student(int fd, CStudent* pstudent);
    void del_student(int fd);
    void del_client(int fd);
    string get_room_name();

    CStudent* get_student_by_fd (int fd);
    CTeacher* get_teacher_by_fd (int fd);
    CCourse * get_course_by_name (string course_name);
    CCourse * get_course_by_id (int id);

    void add_course (CCourse *);

    int  get_teacher_fd ();
    int  get_white_fd ();

    CRoom* get_room_by_fd (int fd);

private:
    CTeacher m_teacher;
    int m_room_id;
    int m_teacher_fd;
    int m_white_fd;
    string m_room_name;
    string m_class_name;
    string m_teacher_name;
    string m_white_board;
    STUDENTMAP m_student_map;
    COURSELIST m_course_list;
    GAMELIST m_game_list;
};

#endif //_C_CLASS_H

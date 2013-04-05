/*
 * class.cpp
 */

#include "room.h"

CRoom::CRoom(int id, string class_name, string white_board):
    m_room_id(id),m_room_name(class_name),m_white_board(white_board) {
}

int CRoom::get_room_id() {
    return m_room_id;
}

void CRoom::set_teacher_fd(int fd) {
    m_teacher_fd = fd;
}

void CRoom::set_teacher_name(string name) {
    m_teacher_name = name;
}

string CRoom::get_teacher_name ()
{
    return this->m_teacher_name;
}

void CRoom::set_class_name(string name) {
    m_class_name = name;
}

void CRoom::set_white_fd(int fd) {
    m_white_fd = fd;
}

void CRoom::add_student(int fd, CStudent* pstudent) {
    m_student_map.insert(pair<int, CStudent*>(fd, pstudent));
    printf("%d:%d---------------%p\n",m_room_id, fd, pstudent);
}

void CRoom::del_student(int fd) {
    STUDENTMAP::iterator it = m_student_map.find(fd);
    if ( m_student_map.end() != it) {
        printf("room [%d] student disconnected fd [%d] name [%s]\n",
                m_room_id,
                it->first,
                it->second->getName().c_str());

        Buf* p = SINGLE->bufpool.malloc();
        MSG_HEAD* p_head = (MSG_HEAD*)p->ptr();
        p_head->cLen = sizeof(MSG_HEAD) + sizeof(TSendStudentStatusReq);
        p_head->cType = ST_SendStudentStatus;

        TSendStudentStatusReq body;
        body.student_id = it->second->getId();
        body.status = 0xFFFFFFFF;
        memcpy(p_head->cData(), &body, sizeof(body));

        p->setsize(p_head->cLen);
        p->setfd(m_teacher_fd);
        SINGLE->sendqueue.enqueue(p);

        delete it->second;
        m_student_map.erase(it);
    }
}

void CRoom::del_client(int fd) {
    if (fd == m_teacher_fd) {
        printf("room [%d] teacher disconnected!\n", m_room_id);
        teacher_disconnect();
        m_teacher_fd = 0;
        return;
    }

    if (fd == m_white_fd) {
        printf("room [%d] teacher disconnected!\n", m_room_id);
        m_white_fd = 0;
        return;
    }
    del_student(fd);
}

CStudent* CRoom::get_student_by_fd (int fd)
{
    STUDENTMAP::iterator it = m_student_map.find(fd);
    if (it != m_student_map.end()) {
        return it->second;
    }
    return NULL;
}

CTeacher* CRoom::get_teacher_by_fd (int fd)
{
    if (fd == this->m_teacher_fd)
        return &m_teacher;
    else
        return NULL;
}

CCourse* CRoom::get_course_by_name (string course_name)
{
    COURSELIST::iterator it;
    for (it = m_course_list.begin (); it!= m_course_list.end (); it++) {
        if ((*it)->getName () == course_name)
            return (*it);
    }
    return NULL;
}

CCourse* CRoom::get_course_by_id (int id)
{
    COURSELIST::iterator it;
    for (it = m_course_list.begin (); it != m_course_list.end (); it++) {
        if ((*it)->getId() == id)
            return (*it);
    }
    return NULL;
}

void CRoom::add_course (CCourse* pCourse)
{
    if (pCourse != NULL)
        m_course_list.push_back (pCourse);
}

int CRoom::get_teacher_fd ()
{
    return this->m_teacher_fd;
}

string CRoom::get_room_name ()
{
    return this->m_room_name;
}

int CRoom::get_white_fd ()
{
    return this->m_white_fd;
}

CRoom* CRoom::get_room_by_fd (int fd)
{
    STUDENTMAP::iterator itt;
    for (itt = m_student_map.begin(); itt != m_student_map.end(); ++itt) {
        printf("[%d][%p]\n", itt->first, itt->second);
    }

    STUDENTMAP::iterator it = m_student_map.find(fd);
    if (it != m_student_map.end()) {
        return this;//it->second;
    }
    else if (fd == this->m_teacher_fd)
        return this;
    else if (fd == this->m_white_fd)
        return this;
    else
        return NULL;
}

int CRoom::reset() {
    STUDENTMAP::iterator it;
    for (it = m_student_map.begin(); it != m_student_map.end();) {
        delete it->second;
        m_student_map.erase(it++);
    }

    COURSELIST::iterator it1;
    for (it1 = m_course_list.begin(); it1 != m_course_list.end();) {
        delete *it1;
        m_course_list.erase(it1++);
    }

    GAMELIST::iterator it2;
    for (it2 = m_game_list.begin(); it2 != m_game_list.end();) {
        delete *it2;
        m_game_list.erase(it2++);
    }
    m_white_fd = 0;
    m_teacher_fd = 0;
    return 0;
}

void CRoom::teacher_disconnect() {
    STUDENTMAP::iterator it;
    for (it = m_student_map.begin(); it != m_student_map.end(); ++it) {
        Buf* p = SINGLE->bufpool.malloc();
        MSG_HEAD* p_head = (MSG_HEAD*)p->ptr();
        p_head->cLen = sizeof(MSG_HEAD) + sizeof(TSendStudentStatusReq);
        p_head->cType = ST_SendStudentStatus;

        TSendStudentStatusReq body;
        body.student_id = 0XFFFFFFFF;
        body.status = 0xFFFFFFFF;
        memcpy(p_head->cData(), &body, sizeof(body));

        p->setsize(p_head->cLen);
        p->setfd(it->first);
        SINGLE->sendqueue.enqueue(p);
    }
}

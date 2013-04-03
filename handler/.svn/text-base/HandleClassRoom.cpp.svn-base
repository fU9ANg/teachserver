
/*
 * HandleClassRoom.cpp
 */

#include "HandleMessage.h"

#include "roommanager.h"
#include "protocol.h"
#include "Buf.h"
#include "LoginCheck.h"

/*
=====================
 
=====================
*/
void CHandleMessage::handleTest (Buf* p)
{
    //todo:
}

/*
=====================
 
=====================
*/
void CHandleMessage::handleChangeScene (Buf* p)
{
    //todo:
    printf ("change scene: %d\n", *(int *)((char *)p->ptr () + sizeof (MSG_HEAD)));
}

/*
=====================
 登录 (所有端)
=====================
*/
void CHandleMessage::handleLogin (Buf* p)
{
    //todo:
    LoginCheck::check(p);
}

/*
=====================
 登录结果 (所有端)
=====================
*/
void CHandleMessage::handleLoginResult (Buf* p)
{
    //todo:
}

/*
=====================
 获得数据库中的课程信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseDBCount (Buf* p)
{
    cout << "CT_GetDBRecordCount\n";
    CHandleMessage::postDBRecordCount (p, 1);
}

/*
=====================
 获得数据库中的课程信息 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseDB (Buf* p)
{
    cout << "CT_GetDBCourseDB\n";
    CHandleMessage::postDBRecord (p, 1);
}

/*
=====================
 设置开启的课程列表 (教师端)
=====================
*/
void CHandleMessage::handleSetCourseGroup (Buf* p)
{
    //todo:SQL_SELECT_USED_COURSE
    cout << "CT_SetCourseGroup\n";
    struct sGetCourseDB course_info;

    try {
        MutexLockGuard guard (DATABASE->m_mutex);
        PreparedStatement* pstmt = DATABASE->preStatement(SQL_SELECT_USED_COURSE);

        sCourseGroup* cg = (sCourseGroup*) (((char*)p->ptr()) + MSG_HEAD_LEN);
        pstmt->setString (1, cg->sGradeName);
        pstmt->setString (2, cg->sCourseGroupName);
        ResultSet* prst = pstmt->executeQuery ();

        while (prst->next())
        {
            memset (&course_info, 0x00, sizeof (course_info));

            CRoom* room = ROOMMANAGER->get_room_by_fd (p->getfd());
            if (room != NULL)
            {
                CCourse* course = new CCourse ();
                if (course != NULL) {
                    course->setId (prst->getInt ("course_id"));
                    course->setName (prst->getString ("course_name"));
                    room->add_course (course);
                }
            }
        }

        delete pstmt;
        delete prst;
    }
    catch (SQLException e) {
        cout << e.what() << endl;
    }

    //


}

/*
=====================
 获得课程列表 (教师端和所有学生端)
=====================
*/
void CHandleMessage::handleGetCourseGroup (Buf* p)
{
    cout << "CT_GetCourseGroup\n";
    string sResult;

    CRoom* room = ROOMMANAGER->get_room_by_fd (p->getfd());
    if (room != NULL)
    {
        CRoom::COURSELIST::iterator it;
        for (it = room->m_course_list.begin (); it != room->m_course_list.end (); ++it) {
            sResult += (*it)->getName();
            sResult += ",";
        }
    }

    struct sGetCourseGroup cList;
    memset (&cList, 0x00, sizeof (sGetCourseGroup));
    strncpy (cList.sCourseList, sResult.c_str(), sResult.size());
    cout << "get courseItem: " << cList.sCourseList << endl;
    cout << "get courseItem: " << sResult.c_str() << endl;

    MSG_HEAD* head = (MSG_HEAD*) p;
    head->cType = CT_GetCourseGroup;
    head->cLen = MSG_HEAD_LEN + sizeof (struct sGetCourseGroup);
    memcpy ((char*)p + MSG_HEAD_LEN, &cList, sizeof (struct sGetCourseGroup));

    p->setsize (head->cLen);
    SINGLE->sendqueue.enqueue (p);

    return;
}

/*
=====================
 获得课程列表的子项数量 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseItemCount (Buf* p)
{
    cout << "CT_GetCourseItemCount\n";
    CHandleMessage::postDBRecordCount (p, 6);
}

/*
=====================
 获得课程列表的子项 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseItem (Buf* p)
{
    cout << "CT_GetCourseItem\n";
    CHandleMessage::postDBRecord (p, 6);
}

/*
=====================
 登出 (所有端)
=====================
*/
void CHandleMessage::handleLogout (Buf* p)
{
    //todo:
}

/*
=====================
 登出结果 (所有端)
=====================
*/
void CHandleMessage::handleLogoutReuslt (Buf* p)
{
    //todo:
}

/*
=====================
 获得教室数据库信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetClassRoomDBCount (Buf* p)
{
    cout << "CT_GetClassRoomDBCount\n";
    CHandleMessage::postDBRecordCount (p, 4);
}

/*
=====================
 获得教室数据库信息 (教师端)
=====================
*/
void CHandleMessage::handleGetClassRoomDB (Buf* p)
{
    cout << "CT_GetClassRoomDB\n";
    CHandleMessage::postDBRecord (p, 4);
}

/*
=====================
 获得教室年级数据库信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetGradeDBCount (Buf* p)
{
    cout << "CT_GetGradeDBCount\n";
    CHandleMessage::postDBRecordCount (p, 2);
}

/*
=====================
 获得教室年级数据库信息 (教师端)
=====================
*/
void CHandleMessage::handleGetGradeDB (Buf* p)
{
    cout << "CT_GetGradeDB\n";
    CHandleMessage::postDBRecord (p, 2);
}

/*
=====================
 获得班级信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetClassDBCount (Buf* p)
{
    cout << "CT_GetClassDBCount\n";
    CHandleMessage::postDBRecordCount (p, 3);
}

/*
=====================
 获得班级信息 (教师端)
=====================
*/
void CHandleMessage::handleGetClassDB (Buf* p)
{
    cout << "CT_GetClassDB\n";
    CHandleMessage::postDBRecord (p, 3);
}

/*
=====================
 进入教室 (所有学生端)
=====================
*/
void CHandleMessage::handleLoginClassRoom (Buf* p)
{
    struct sLoginOutClassRoom st_login_class_room;
    memcpy(&st_login_class_room,
            (char*)p->ptr() + sizeof(MSG_HEAD),
            sizeof(struct sLoginOutClassRoom));
    CRoom* proom = ROOMMANAGER->get_room_by_name(st_login_class_room.sClassRoomName);
    if( NULL == proom) {
        SINGLE->bufpool.free(p);
        LOG(ERROR) << "cat find class room " << st_login_class_room.sClassRoomName <<endl;
        printf("cat find class room [%s]\n", st_login_class_room.sClassRoomName);
        return;
    }
    proom->set_teacher_fd(p->getfd());
    proom->set_teacher_name(st_login_class_room.sTeacherName);
    proom->set_class_name(st_login_class_room.sClassName);
    printf("Teacher login class room [%d] success!\n", proom->get_room_id());

    SINGLE->bufpool.free(p);
    //todo:
}

/*
=====================
 退出教室 (教师端和所有学生端)
=====================
*/
void CHandleMessage::handleLogoutClassRoom (Buf* p)
{
    //todo:
}

/*
=====================
 获得学生信息 (所有端)
=====================
*/
void CHandleMessage::handleGetStudentInfo (Buf* p)
{
    //todo:
}

/*
=====================
 获得所有学生列表数量 (所有端)
=====================
*/
void CHandleMessage::handleGetAllStudentInfoCount (Buf* p)
{
    cout << "CT_GetAllStudentInfoCount" << endl;
    CHandleMessage::postDBRecordCount (p, 5);
}

/*
=====================
 获得所有学生列表 (所有端)
=====================
*/
void CHandleMessage::handleGetAllStudentInfo (Buf* p)
{ 
    cout << "CT_GetAllStudentInfo" << endl;
    CHandleMessage::postDBRecord (p, 5);
}

/*
=====================
 早退 (教师端)
 早退通知给 (学生端)
=====================
*/
void CHandleMessage::handleLeaveEarly (Buf* p)
{
    //todo:
}

/*
=====================
 早退确认 (学生端) *
=====================
*/
void CHandleMessage::handleConfirmLeaveEarly (Buf* p)
{
    //todo:
}

/*
=====================
 获得教师信息 (所有学生端和教师端)
=====================
*/
void CHandleMessage::handleGetTeacherInfo (Buf* p)
{
    //todo:
}

/*
=====================
 锁定学生端 (教师端) *
 锁定学生端 (学生端) *
=====================
*/
void CHandleMessage::handleLockStudent (Buf* p)
{
    if (p == NULL)
        return;

    cout << "process: CT_LockStudent" << endl;
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();

    if (head->cType == CT_LockStudent) {
        postTeacherToAllStudent (p, ST_LockStudent);
    }

    return;
}

/*
=====================
 
=====================
*/
void CHandleMessage::handleSelectedClassRoom (Buf* p)
{
    //todo:
    TSelectedClassRoom* pp = (TSelectedClassRoom*)((char*)p->ptr() + sizeof(MSG_HEAD));

    //CClass* pclass = CLASSMANAGER->get_class(pp->classroom_id);
    CRoom* proom = ROOMMANAGER->get_room(pp->classroom_id);
    if (MCT_STUDENT == pp->client_type) {
        CStudent* pstudent = new CStudent();
        proom->add_student(p->getfd(), pstudent);
        printf("add a student[%d][%p]\n", p->getfd(), pstudent);
    }
    if (MCT_WHITEBOARD == pp->client_type) {
        printf("white board login classroom[%d]", proom->get_room_id());
        proom->set_white_fd(p->getfd());
    }
    p->reset();
    SINGLE->bufpool.free(p);
}

/*
=====================
 
=====================
*/
void CHandleMessage::handleCourseFinished (Buf* p)
{
    //todo:
}


/*
=====================
 CT_GetDBRecordFinished, // 请求所有数据库记录是否完成
 ST_GetDBRecordFinished, // 服务器回应数据库记录是否完成
=====================
*/
void CHandleMessage::handleDBRecordFinished (Buf* p)
{
    cout << "CT_GetDBRecordFinished and ST_GetDBRecordFinished" << endl;
    if (p == NULL);
        return;
#if 0
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();
    struct sDBRecordFinished finished;
    finished.iFlagFinished = 1;

    if (head->cType == CT_GetDBRecordFinished) {
        head->cLen = sizeof (MSG_HEAD) + sizeof (struct sDBRecordFinished);
        head->cType = ST_GetDBRecordFinished;
        memcpy (head->cData(), &finished, sizeof (struct sDBRecordFinished));
        p->setsize (head->cLen);
        SINGLE->sendqueue.enqueue (p);
    }
#endif
    return;
}

void CHandleMessage::handleGetCourseItemKeyInfoReq (Buf* p) {
    MSG_HEAD* p_head = (MSG_HEAD*)p->ptr();
    string keys_info;

    GetCourseItemKeyInfoRsp rsp;

    try {
        MutexLockGuard guard (DATABASE->m_mutex);
        PreparedStatement* pstmt = DATABASE->preStatement(SQL_SELECT_ITEM_KEYS);
        pstmt->setInt(1, *(int*)p_head->cData());
        ResultSet* rst = pstmt->executeQuery();
        while(rst->next()) {
            strcpy(rsp.keys, rst->getString("keys_info").c_str());
        }
        delete rst;
        delete pstmt;
    }catch( SQLException& e) {
        printf(" %s %d:%s", __FUNCTION__, __LINE__, e.what());
        LOG(ERROR) <<e.what()<<endl;
        SINGLE->bufpool.free(p);
        return;
    }

    p_head->cLen = sizeof(MSG_HEAD) + sizeof(GetCourseItemKeyInfoRsp);
    p_head->cType = CT_GetCourseItemKeyInfoRsp;
    memcpy(p_head->cData(), &rsp, sizeof(rsp));
    p->setsize(p_head->cLen);
    SINGLE->sendqueue.enqueue(p);
}

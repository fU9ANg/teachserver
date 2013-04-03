
/*
 * HandleMessage.cpp
 */

#include "HandleMessage.h"

#include "protocol.h"
#include "Buf.h"
#include "roommanager.h"
#include "teacher.h"
#include "Single.h"

/////////////////////
HANDLEMAP CHandleMessage::m_HandleMap;


/*
=====================
 转发信息的通用接口
=====================
*/
bool CHandleMessage::postMessage (Buf* p, enum CommandType iCommandType, void* data, unsigned int iLen)
{
    if (p == NULL)
        return false;

    MSG_HEAD* head = (MSG_HEAD*)p->ptr();
    head->cLen = sizeof (MSG_HEAD);
    head->cType = iCommandType;

    if (data != NULL) {
        head->cLen = head->cLen + iLen;
        (void) memcpy ((char*)p->ptr() + sizeof (MSG_HEAD), (char*)data, iLen);
    }

    p->setsize (head->cLen);
    SINGLE->sendqueue.enqueue (p);

    return true;
}

/*
=====================
 转发教师端数据到白板端
=====================
*/
bool CHandleMessage::postTeacherToWhite (Buf* p, enum CommandType iCommandType)
{
    if (p == NULL)
        return false;

    CRoom* pc = ROOMMANAGER->get_room_by_fd (p->getfd());

    if (pc != NULL && pc->get_teacher_fd() == p->getfd()) {

        MSG_HEAD* head = (MSG_HEAD*)p->ptr();

        head->cType = iCommandType;
        p->setfd (pc->get_white_fd());
        p->setsize (head->cLen);
        SINGLE->sendqueue.enqueue (p);
    }
    else {
        cout << "Error: not found 'teacher_fd' in Room" << endl;
        SINGLE->bufpool.free(p);
        return false;
    }
    return true;
}

/*
=====================
 转发学生端数据到白板端
=====================
*/
bool CHandleMessage::postStudentToWhite (Buf* p, enum CommandType iCommandType)
{
    if (p == NULL)
        return false;

    CRoom* pc = ROOMMANAGER->get_room_by_fd (p->getfd());

    if (pc != NULL && pc->get_student_by_fd (p->getfd()) != NULL) {
        MSG_HEAD* head = (MSG_HEAD*)p->ptr();

        head->cType = iCommandType;
        p->setfd (pc->get_white_fd());
        p->setsize (head->cLen);
        SINGLE->sendqueue.enqueue (p);
    }
    else {
        cout << "Error: not found 'student_fd' in Room" << endl;
        SINGLE->bufpool.free(p);
        return false;
    }

    return true;
}

/*
=====================
 转发教师端数据到所有学生端
=====================
*/
bool CHandleMessage::postTeacherToAllStudent (Buf* p, enum CommandType iCommandType)
{
    if (p == NULL)
        return false;

    int iLen = ((MSG_HEAD*)p->ptr())->cLen;
    int iHeadLen = sizeof (MSG_HEAD);
    Buf* pbuf = NULL;

    CRoom* pc = ROOMMANAGER->get_room_by_fd (p->getfd());
    if (pc != NULL) {

        CRoom::STUDENTMAP::iterator it;
        for (it = pc->m_student_map.begin(); \
             it != pc->m_student_map.end (); ++it)
        {
            pbuf = SINGLE->bufpool.malloc ();
            if (pbuf != NULL) {
                MSG_HEAD* head = (MSG_HEAD*)pbuf->ptr();
                head->cLen = iLen;
                head->cType = iCommandType;
                if (iLen > iHeadLen) {
                    memcpy (head->cData(), (char*)p->ptr() + iHeadLen, iLen - iHeadLen);
                }
                pbuf->setsize (head->cLen);
                pbuf->setfd (it->first);
                SINGLE->sendqueue.enqueue (pbuf);
            }
            else {
                cout << "Error: out of memory" << endl;
                p->reset();
                pbuf->reset();
                SINGLE->bufpool.free(p);
                SINGLE->bufpool.free(pbuf);
                return false;
            }
        }
    }
    else {
        cout << "Error: not found 'teacher_fd' in Room" << endl;
        p->reset();
        SINGLE->bufpool.free(p);
        return false;
    }

    p->reset();
    SINGLE->bufpool.free(p);

    return true;
}

/*
=====================
 转发教师端数据到学生端
=====================
*/
bool CHandleMessage::postTeacherToStudent (Buf* p, enum CommandType iCommandType, int iStuId)
{
    if (p == NULL)
        return false;

    CRoom* pc = ROOMMANAGER->get_room_by_fd (p->getfd());
    if (pc != NULL && pc->get_teacher_fd() == p->getfd())
    {
        CRoom::STUDENTMAP::iterator it;
        for (it = pc->m_student_map.begin(); \
             it != pc->m_student_map.end (); ++it)
        {
            if (it->second->getId() == iStuId) {
                MSG_HEAD* head = (MSG_HEAD*)p->ptr();

                head->cType = iCommandType;
                p->setfd (it->first);
                p->setsize (head->cLen);
                SINGLE->sendqueue.enqueue (p);
            }
        }
        cout << "Error: not found 'student_fd' in Room" << endl;
        return false;
    }
    else {
        cout << "Error: not found 'teacher_fd' in Room" << endl;
        return false;
    }

    return true;
}

/*
=====================
 获得数据库表纪录数量
=====================
*/
bool CHandleMessage::postDBRecordCount (Buf* p, int iCase)
{
    char str[1024] = "SELECT count(*) AS ccount FROM ";

    if (NULL == p) {
        printf("null buf\n");
        return false;
    }
    printf (" postDBRecordCount ..., iCase=%d\n", iCase);
#if 1
    if (iCase == 1) {
        strcat (str, "course_group_course AS cgc, course_group AS cg, course AS c, grade AS g, grade_course AS gc WHERE  cgc.group_id = cg.group_id AND cgc.course_id = c.course_id AND gc.grade_id = g.grade_id AND c.course_id = gc.course_id");
    }
    else if (iCase == 2) {
        strcat (str, "grade");
    }
    else if (iCase == 3) {
        strcat (str, "class");
    }
    else if (iCase == 4) {
        strcat (str, "classroom");
    }
    else if (iCase == 5) {
        strcat (str, "student");
    }
    else if (iCase == 6) {
        strcat (str, "course_item AS ci, course AS c, item AS i WHERE ci.course_id=c.course_id AND ci.item_id=i.item_id AND c.course_name=?");
    }
#endif

    // dbCount.count = 100;
    //
#if 0
    struct sDBCount dbCount;
    dbCount.count = 5;
    MSG_HEAD *head = (MSG_HEAD*) buf->ptr();
    head->cLen = sizeof (MSG_HEAD) + sizeof (dbCount);
    head->cType = CT_GetClassRoomDBCount;
    memcpy (head->cData(), &dbCount, sizeof (dbCount));

    buf->setsize (head->cLen);
    SINGLE->sendqueue.enqueue (buf);
#endif
#if 1

    try {
        MutexLockGuard guard(DATABASE->m_mutex);
        PreparedStatement* pstmt = DATABASE->preStatement(str);
        if (iCase == 6) {
            sGetCourseItem* ci = (sGetCourseItem *) ((char*)((MSG_HEAD*)p->ptr()) + sizeof (MSG_HEAD));
            pstmt->setString (1, ci->sCourseName);
        }
        ResultSet* prst = pstmt->executeQuery ();
        while (prst->next ()) {
            struct sDBCount dbCount;
            dbCount.count = prst->getInt ("ccount");
            printf ("get db count: %d\n", dbCount.count);
            MSG_HEAD* head = (MSG_HEAD*)p->ptr();
            head->cLen = MSG_HEAD_LEN + sizeof (dbCount);

            if (iCase == 1)
                head->cType = CT_GetCourseDBCount;
            else if (iCase == 2)
                head->cType = CT_GetGradeDBCount;
            else if (iCase == 3)
                head->cType = CT_GetClassDBCount;
            else if (iCase == 4)
                head->cType = CT_GetClassRoomDBCount;
            else if (iCase == 5)
                head->cType = CT_GetAllStudentInfoCount;
            else if (iCase == 6)
                head->cType = CT_GetCourseItemCount;

            memcpy (head->cData(), &dbCount, sizeof (dbCount));

            p->setsize (head->cLen);
            SINGLE->sendqueue.enqueue (p);
        }
        delete pstmt;
        delete prst;
    }
    catch (SQLException e) {
        printf ("%s\n", e.what ());
    }
#endif
    return true;
}

/*
=====================
 获得数据库表纪录
=====================
*/
bool CHandleMessage::postDBRecord (Buf* buf, int iCase)
{
    if (NULL == buf) {
        printf("null buf\n");
        return false;
    }

    MSG_HEAD head;

    try {
        MutexLockGuard guard(DATABASE->m_mutex);
        PreparedStatement* pstmt = NULL;

        if (iCase == 1)
            pstmt = DATABASE->preStatement (SQL_SELECT_COURSE_DB);
        else if (iCase == 2)
            pstmt = DATABASE->preStatement (SQL_SELECT_GRADE_DB);
        else if (iCase == 3)
            pstmt = DATABASE->preStatement (SQL_SELECT_CLASS_DB);
        else if (iCase == 4)
            pstmt = DATABASE->preStatement (SQL_SELECT_CLASSROOM_DB);
        else if (iCase == 5)
            pstmt = DATABASE->preStatement (SQL_SELECT_STUDENT_DB);
        else if (iCase == 6) {
            pstmt = DATABASE->preStatement (SQL_SELECT_COURSEITEM_DB);
            sGetCourseItem* ci = (sGetCourseItem *) ((char*)((MSG_HEAD*)buf->ptr()) + sizeof (MSG_HEAD));
            pstmt->setString (1, ci->sCourseName);
        }
        else {
            cout << "error: index" << endl;
            return false;
        }
        ResultSet* prst = pstmt->executeQuery();
        unsigned int index = 0, type = 0;
        while(prst->next()) {
            printf ("index = %d------------------------------------------------------\n", index);
            if (iCase == 1) {
                memset (&head, 0x00, sizeof (head));
                //head.cType = CT_GetCourseDB * 100 + index++;
                type = 5000 + index++;
                memcpy (&head.cType, &type, sizeof (unsigned int));
                head.cLen = sizeof(MSG_HEAD) + sizeof(struct sGetCourseDB);
                struct sGetCourseDB course_info;

                strcpy(course_info.sGradeName, prst->getString ("grade_name").c_str());
                strcpy(course_info.sGroupName, prst->getString ("group_name").c_str());
                strcpy(course_info.sCourseName, prst->getString("course_name").c_str());

                course_info.iLanguage   = prst->getInt ("language");
                course_info.iArt        = prst->getInt ("art");
                course_info.iCommunity  = prst->getInt ("community");
                course_info.iHealth     = prst->getInt ("health");
                course_info.iScience    = prst->getInt ("science");

                Buf* p = SINGLE->bufpool.malloc ();
                memcpy(p->ptr(), &head, sizeof(MSG_HEAD));
                memcpy((char*)p->ptr() + sizeof(MSG_HEAD), &course_info, sizeof(struct sGetCourseDB));
                p->setfd(buf->getfd());
                p->setsize(head.cLen);
                SINGLE->sendqueue.enqueue(p);
            }

            else if (iCase == 2) {
                memset (&head, 0x00, sizeof (head));
                type = 3000 + index++;
                memcpy (&head.cType, &type, sizeof (unsigned int));
                //head.cType = CT_GetGradeDB;
                head.cLen = sizeof (MSG_HEAD)+ sizeof (struct sGetGradeDB);
                struct sGetGradeDB grade_info;

                strcpy (grade_info.sGradeName, prst->getString ("grade_name").c_str());

                Buf* p = SINGLE->bufpool.malloc ();
                memcpy (p->ptr(), &head, sizeof(MSG_HEAD));
                memcpy ((char *)p->ptr() + sizeof(MSG_HEAD), &grade_info, sizeof(struct sGetGradeDB));
                p->setfd (buf->getfd ());
                p->setsize(head.cLen);
                SINGLE->sendqueue.enqueue (p);
            }

            else if (iCase == 3) {
                memset (&head, 0x00, sizeof (head));
                type = 4000 + index++;
                memcpy (&head.cType, &type, sizeof (unsigned int));
                //head.cType = CT_GetClassDB;
                head.cLen = sizeof(MSG_HEAD)+ sizeof (struct sGetClassDB);
                struct sGetClassDB class_info;

                strcpy (class_info.sClassName, prst->getString ("class_name").c_str());

                Buf* p = SINGLE->bufpool.malloc ();
                memcpy (p->ptr(), &head, sizeof (MSG_HEAD));
                memcpy ((char *)p->ptr() + sizeof (MSG_HEAD), &class_info, sizeof (struct sGetClassDB));
                p->setfd (buf->getfd ());
                p->setsize(head.cLen);
                SINGLE->sendqueue.enqueue (p);
            }

            else if (iCase == 4) {
                memset (&head, 0x00, sizeof (head));
                //head.cType = CT_GetClassRoomDB;
                type = 6000 + index++;
                memcpy (&head.cType, &type, sizeof (unsigned int));
                head.cLen = sizeof(MSG_HEAD) + sizeof (struct sGetClassRoomDB);
                struct sGetClassRoomDB room_info;

                strcpy (room_info.sClassRoomName, prst->getString ("classroom_name").c_str());

                Buf* p = SINGLE->bufpool.malloc ();
                memcpy (p->ptr(), &head, sizeof (MSG_HEAD));
                memcpy ((char *)p->ptr() + sizeof (MSG_HEAD), &room_info, sizeof (struct sGetClassRoomDB));
                p->setfd (buf->getfd ());
                p->setsize(head.cLen);
                SINGLE->sendqueue.enqueue (p);
            }

            else if (iCase == 5) {
                memset (&head, 0x00, sizeof (MSG_HEAD));
                type = 10000 + index++;
                memcpy (&head.cType, &type, sizeof (unsigned int));
                cout << "begin:-head.cType = " << head.cType << endl;
                head.cLen = sizeof (MSG_HEAD) + sizeof (struct sGetAllStudentInfo);
                struct sGetAllStudentInfo stu_info;

                strcpy (stu_info.sPicName, prst->getString ("picture_name").c_str());
                stu_info.iStudentId= prst->getInt ("student_id");

                cout << "stu_info.iStudentId:" << stu_info.iStudentId << endl;
                cout << "stu_info.sPicName:" << stu_info.sPicName << endl;

                Buf* p = SINGLE->bufpool.malloc ();
                memcpy (p->ptr(), &head, sizeof (MSG_HEAD));
                memcpy ((char *)p->ptr() + sizeof (MSG_HEAD), &stu_info, sizeof (struct sGetAllStudentInfo));
                p->setfd (buf->getfd ());
                p->setsize(head.cLen);
                SINGLE->sendqueue.enqueue (p);
                cout << "address = " << p << endl;
                cout << "ended:-head.cLen = " << head.cLen << endl;
                cout << "ended:-head.cType = " << head.cType << endl;
            }

            else if (iCase == 6) {
                memset (&head, 0x00, sizeof (head));
                type = 7000 + index++;
                memcpy (&head.cType, &type, sizeof (unsigned int));
                //head.cType = CT_GetCourseItem;
                head.cLen = sizeof(MSG_HEAD) + sizeof (struct sCourseItem);
                struct sCourseItem course_item;

                strcpy (course_item.sCourseName, prst->getString ("course_name").c_str());
                strcpy (course_item.sItemName, prst->getString ("item_name").c_str());

                Buf* p = SINGLE->bufpool.malloc ();
                memcpy (p->ptr(), &head, sizeof(MSG_HEAD));
                memcpy ((char *)p->ptr() + sizeof(MSG_HEAD), &course_item, sizeof (struct sCourseItem));
                p->setfd (buf->getfd ());
                p->setsize(head.cLen);
                SINGLE->sendqueue.enqueue (p);
            }
            else {
                cout << "error: index" << endl;
                return false;
            }

        }
#if 1
        do {
            cout << "send finished flags -----------" << endl;
            Buf* p = SINGLE->bufpool.malloc ();
            MSG_HEAD* phead = (MSG_HEAD*)p->ptr();
            struct sDBRecordFinished finished;
            finished.iFlagFinished = 1;

            phead->cLen = sizeof (MSG_HEAD) + sizeof (struct sDBRecordFinished);
            phead->cType = ST_GetDBRecordFinished;
            memcpy (((char*)p->ptr()) + MSG_HEAD_LEN, &finished, sizeof (struct sDBRecordFinished));
            p->setfd (buf->getfd());
            p->setsize (phead->cLen);
            SINGLE->sendqueue.enqueue (p);
        } while (0);
#endif
        delete pstmt;
        delete prst;
    }
    catch(SQLException e){
        LOG(ERROR) << e.what() << std::endl;
    }

    buf->reset();
    SINGLE->bufpool.free(buf);

    return true;
}


/*
 * HandleRainbowValley.cpp
 */

#include "HandleMessage.h"

#include "protocol.h"
#include "Buf.h"
#include "roommanager.h"
#include "teacher.h"
#include "Single.h"
#include "room.h"

#include "makehouse.h"

/*
=====================
 获得房子数量
=====================
*/
void CHandleMessage::handleRainbowValley_HouseNum (Buf* p)
{
    cout << "CT_RainbowValley_HouseNum" << endl;

    CRoom* p_room = ROOMMANAGER->get_room_by_fd (p->getfd());
    if (p_room == NULL)
        return;

    int groupSize = m_buildhouse_groups.size();

    MSG_HEAD* head = (MSG_HEAD* )(char*) p->ptr();
    head->cLen = MSG_HEAD_LEN + sizeof (sRainbowValley_House_Num);
    head->cType = ST_RainbowValley_HouseNum;
    sRainbowValley_House_Num* p_house_num = \
            (sRainbowValley_House_Num)((char*)p->ptr() + MSG_HEAD_LEN);

    cout << "group Size of RainbowValley" << endl;
    p_house_num->num = groupSize;

    p->setsize (head->cLen);
    SINGLE->sendqueue.enqueue (p);
}

/*
=====================
 获得房子信息
=====================
*/
void CHandleMessage::handleRainbowValley_HouseInfo (Buf* p)
{
    cout << "CT_RainbowValley_HouseInfo" << endl;

    CRoom* p_room = ROOMMANAGER->get_room_by_fd (p->getfd());
    if (p_room == NULL)
        return;
    CGroup* p_group = p_room->get_group_by_fd (p->getfd());
    if (p_group == NULL)
        return;
}

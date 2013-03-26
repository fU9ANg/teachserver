
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

using namespace std;

class cRoom
{
private:
    string m_name;
    string m_whiteboard;

public:
    cRoom();
    ~cRoom ();

    string getName (void);
    void setName (string& sName);

    string getWhiteBoardName (void);
    void setWhiteBoardName (string& sName);
};

#endif //_C_ROOM_H
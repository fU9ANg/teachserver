
/*
 * student.h
 */

#ifndef	_C_STUDENT_H
#define _C_STUDENT_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class CStudent
{
private:
	string      m_StuName;
	string      m_AccountName;
	bool        m_onLine;
    int         m_Id;
    int         m_Socket;
    string      m_picture_name;

public:
	CStudent ();
	CStudent (string& s1, string& s2, string& acc, bool line):\
		m_StuName (s1+s2), m_AccountName (acc), m_onLine (line) {}
	~CStudent ();

	void setName (string& s1, string& s2);
	string getName (void);

	void setAccount (string& acc);
	string getAccount (void);

	void setOnLine (bool b);
	bool getOnLine (void);

    void setId(int id);
    int getId();

    void setSocket(int sock);
    int getSocket();

    void setPictureName (string name);
    string getPictureName (void);
};

#endif //_C_STUDENT_H

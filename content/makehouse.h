
#ifndef _MAKEHOUSE_H_
#define _MAKEHOUSE_H_

#include <map>
#include <stdio.h>
#include <iostream>
#include "student.h"
#include "Mutex.h"
#include "Buf.h"
#include "Single.h"

using namespace std;

class CNode{
    public:
        CNode();
        CNode(int x, int y);
        ~CNode();
        int move(int x,int y);
        int move(int x,int y, double angle, double zoom);
        bool lock(int user_id);
        bool unlock(int user_id);
        int get_node_id();
        void set_node_id(int node_id);
        void set_name(string name);
        void get_location(int& x, int& y);
        void get_location(int& x, int& y, double& angle, double& zoom);
    private:
        int m_position_x; /**x*/
        int m_position_y;
        int m_layer; //层次
        int m_user_id;
        int m_node_id;
        double m_angle; //角度
        double m_zoom; //放大倍数
        char m_path[512];
        string m_name;
};

class CMakeHouse{
    public:
        CMakeHouse();
        ~CMakeHouse();
        bool lock(int user_id, int node_id);
        bool unlock(int user_id, int node_id);
        int add(int user_id, CNode* p_node);
        int move(int node_id, int to_x, int to_y);

        /**
         * @brief 将节点上移count层
         * @param  node_id   需要上调的节点id
         * @param  count     上移层数
         */
        int layer_up(int node_id, int count);

        /**
         * @brief 将节点下移count层
         * @param  node_id   需要下调的节点id
         * @param  count     下移层数
         */
        int layer_down(int node_id, int count);
        
    public:
        typedef std::map  <int, CNode*> NODEMAP;
        typedef std::list <CNode*> NODELIST;

    private:
        NODEMAP    m_node_map;
        NODELIST   m_node_list;

        list<CNode*> m_node_layer_list;
        MutexLock m_node_layer_list_lock;

        list<CNode*>::iterator get_iterator_by_node_id(int node_id);
};

class CGroup
{
    typedef std::map  <int, CStudent*> STUDENTMAP;   /* <student_fd, CStudent> */
    
    private:
        string m_group_name;
        CMakeHouse m_make_house;
        STUDENTMAP m_student_map;
        int m_white_position;

    public:
        CGroup (string name);
        ~CGroup ();
        CMakeHouse* get_make_house (void);
        bool add_student_to_group (int fd, CStudent* stu);
        CGroup* get_group_by_fd (int fd);
        CStudent* get_student_by_fd (int fd);
        void broadcast(Buf* p);

};

#endif

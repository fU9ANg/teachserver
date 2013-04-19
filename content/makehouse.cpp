#include "makehouse.h"
CNode::CNode(){
};

CNode::CNode(int x, int y){
    m_position_x = x;
    m_position_y = y;
};

CNode::~CNode(){
}

int CNode::move(int x,int y) {
    m_position_x = x;
    m_position_y = y;
    return 0;
}

int CNode::move(int x,int y, double angle, double zoom) {
    m_position_x = x;
    m_position_y = y;
    m_angle = angle;
    m_zoom = zoom;
    return 0;
}

bool CNode::lock(int user_id) {
    if ( 0 == m_user_id) {
        m_user_id = user_id;
        return true;
    }
    return false;
}

bool CNode::unlock(int user_id) {
    if ( 0 != m_user_id) {
        m_user_id = 0;
        return true;
    }
    return false;
}
int CNode::get_node_id() {
    return m_node_id;
}

void CNode::set_node_id(int node_id) {
    m_node_id = node_id;
}

void CNode::set_name(string name) {
    m_name = name;
}

void CNode::get_location(int& x, int& y) {
    x = m_position_x;
    y = m_position_y;
}
void CNode::get_location(int& x, int& y, double& angle, double& zoom) {
    x = m_position_x;
    y = m_position_y;
    angle = m_angle;
    zoom = m_zoom;
}

CMakeHouse::CMakeHouse(){
}

CMakeHouse::~CMakeHouse(){
}

bool CMakeHouse::lock(int user_id, int node_id) {
    return true;
}
bool CMakeHouse::unlock(int user_id, int node_id) {
    return true;
}

int CMakeHouse::add(int user_id, CNode* p_node) {
    m_node_map.insert(pair<int, CNode*>(user_id, p_node));
    return 0;
}

list<CNode*>::iterator CMakeHouse::get_iterator_by_node_id(int node_id) {
    list<CNode*>::iterator iter;
    for( iter = m_node_layer_list.begin();
         iter != m_node_layer_list.end(); iter++ ) {
        if ( (*iter)->get_node_id() == node_id) {
            return iter;
        }
    }
    return m_node_layer_list.end();
}

int CMakeHouse::layer_up(int node_id, int count) {
    MutexLockGuard guard(this->m_node_layer_list_lock);
    list<CNode*>::iterator iter = get_iterator_by_node_id(node_id);
    if (iter == m_node_layer_list.end()) {
        return -1;
    }
    int i = 0;
    for (i = 0; i < count; i++) {
        if (iter != m_node_layer_list.begin()){
            std::swap(*iter, *(iter--));
        } else{
            break;
        }
    }
    return i;
}

int CMakeHouse::layer_down(int node_id, int count) {
    MutexLockGuard guard(this->m_node_layer_list_lock);
    list<CNode*>::iterator iter = get_iterator_by_node_id(node_id);
    if (iter == m_node_layer_list.end()) {
        return -1;
    }
    int i = 0;
    for (i = 0; i < count; i++) {
        if (iter != m_node_layer_list.end()){
            std::swap(*iter, *(iter++));
        } else{
            break;
        }
    }
    return i;
}

int CMakeHouse::move(int node_id, int to_x, int to_y) {
    NODEMAP::iterator iter = m_node_map.find(node_id);
    if (iter != m_node_map.end()){
        iter->second->move(to_x, to_y);
    }
    return 0;
}

////////// Class CGroup //////////
CGroup::CGroup (string name) : m_group_name(name)
{
}

CGroup::~CGroup (void)
{
    //
}

CMakeHouse* CGroup::get_make_house (void)
{
    return &m_make_house;
}

bool CGroup::add_student_to_group (int fd, CStudent* stu)
{
    if (fd > 0 && stu)
    {
        m_student_map.insert (std::pair<int, CStudent*> (fd, stu));
        return true;
    }

    return false;
}

CGroup* CGroup::get_group_by_fd (int fd)
{
    STUDENTMAP::iterator it;
    for (it=m_student_map.begin(); it!=m_student_map.end();++it)
    {
        if (it->first == fd)
            return this;
    }

    return NULL;
}

CStudent* CGroup::get_student_by_fd (int fd)
{
    STUDENTMAP::iterator it;
#if 1
    it = m_student_map.find (fd);
    if (it != m_student_map.end())
    {
        return it->second;
    }
#else
    for (it = m_student_map.begin(); it != m_student_map.end(); it++)
    {
        if (it->first == fd)
            return it->second;
    }
#endif
    return NULL;
}

void CGroup::broadcast(Buf* p) {
    STUDENTMAP::iterator it;
    for (it=m_student_map.begin(); it!=m_student_map.end();++it) {
        Buf* p_buf = SINGLE->bufpool.malloc();
        *p_buf = *p;
        SINGLE->sendqueue.enqueue(p_buf);
    }
}


#include "RecvTask.h"
#include "LoginCheck.h"
RecvTask::RecvTask() {
}

RecvTask::~RecvTask() {
}

void login_check (Buf* buf)
{
    LoginCheck* lc = new LoginCheck ();
    lc->check (buf);
}

void process_scene (Buf* buf)
{
    printf ("change scene: %d\n", *(int *)((char *)buf->ptr () + sizeof (MSG_HEAD)));
#if 0
    int sendData = 3;

    MSG_HEAD* head = (MSG_HEAD*) buf->ptr ();
    head->cLen = 12;
    head->cType = CT_Test;
    memcpy (head->cData(), &sendData, sizeof (int));

    buf->setsize (head->cLen);
    SINGLE->sendqueue.enqueue (buf);
#endif
    //
}

void getDBRecordCount (Buf* buf, int iCase)
{
    //todo:
}

void getDBRecord (Buf* buf, int iCase)
{
    //todo:
}

void handle_selected_class(Buf* p) {
#if 0
    printf ("CT_SelectedClassRoom: %d\n", *(int *)((char *)p->ptr () + sizeof (MSG_HEAD)));

    TSelectedClassRoom* pp = (TSelectedClassRoom*)((char*)p->ptr() + sizeof(MSG_HEAD));

    CClass* pclass = CLASSMANAGER->get_class(pp->classroom_id);
    if (MCT_STUDENT == pp->client_type) {
        CStudent* pstudent = new CStudent();
        pclass->add_student(p->getfd(), pstudent);
    }
    if (MCT_WHITEBOARD == pp->client_type) {
        pclass->set_white_fd(p->getfd());
    }
    p->reset();
    SINGLE->bufpool.free(p);
#endif
}

void handle_show_sprite_animation (Buf* p)
{
#if 0
    printf ("CT_ShowSpriteAnimation\n");
    CClass* pc = CLASSMANAGER->get_class_by_fd (p->getfd ());
    
    if (pc != NULL && p->get_teacher_fd() == p->getfd()) {
        MSG_HEAD head;
        head.cLen = sizeof (MSG_HEAD);
	head.cType = ST_ShowSpriteAnimation;
        p->setfd (pc->get_white_fd ());
        p->setsize (head.cLen);
        SINGLE->sendqueue.enqueue (p);	
    }
    else {
        cout << "teacher_fd not found in CLASS of CLASSMANAGER" << endl;
    }
    return;
#endif
}
int RecvTask::work ()
{
    while(true) {
        Buf* p = NULL;
        if (0 != SINGLE->recvqueue.dequeue(p, 3)) {
            continue;
        }

        if (p == NULL) {
            cout << "ERROR: p==NULL in RecvTask::work()" << endl;
            return (0);
        }

        MSG_HEAD* head = (MSG_HEAD*) p->ptr();
        if (head != NULL)
        {
            cout << "recvTask: type=" << head->cType << endl;
            handlefunc pfun = CHandleMessage::getHandler (head->cType); 
            if (NULL == pfun) {
                printf("function pointer error[%d]!\n",head->cType);
                continue;
            }
            pfun(p);
        }
    }
    return 0;
}

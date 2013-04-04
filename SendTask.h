#ifndef SENDTASK_H_
#define SENDTASK_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "task.h"
class SendTask: public task
{
    public:
        SendTask();
        ~SendTask();
        virtual int work();
};

#endif

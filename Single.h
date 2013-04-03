#ifndef _GLOBAL_DATA_H_
#define _GLOBAL_DATA_H_
#include <stdio.h>
#include "AtomicT.h"
#include "QueueT.h"
#include "PoolT.h"
#include "Buf.h"
#include "twomapT.h"
class Single {
    public:
        ~Single();
        static class Single* instance();
        QueueT<Buf*> recvqueue;
        QueueT<Buf*> sendqueue;
        PoolT<Buf> bufpool;

    private:
        Single();
        static class Single* p_;
};
#define SINGLE Single::instance()
#endif

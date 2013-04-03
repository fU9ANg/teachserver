#include "SendTask.h"
SendTask::SendTask() {
}

SendTask::~SendTask() {
}

int SendTask::work() {
    while(true){
        Buf* p = NULL;
        if (0 != SINGLE->sendqueue.dequeue(p, 3)) {
            continue;
        }

        int fd = p->getfd();

        if (0 == fd) {
            printf(" fd = 0 !\n");
            continue;
        }

#if 0
        MSG_HEAD* pp = (MSG_HEAD*)p->ptr();
        if ( pp->cType > 9999 ) {
            struct sGetAllStudentInfo* xxx = (struct sGetAllStudentInfo*)pp->cData();
            printf("id %d pic %s  --  len:=%d\n", xxx->iStudentId, xxx->sPicName, pp->cLen);

        }

        unsigned int len = 0;
        int cnt;
        while (len < p->size()) {
            cnt = send(fd, (char *)p->ptr() + len, p->size() - len, 0);
            if (cnt == -1) {
                cout << "send erroooooooooooooooooooooor" << endl;
                break;
            }
            len += cnt;
        }

        printf ("ERRNO: %d, message:%s len = %d, p->size() = %ld\n", errno, strerror (errno), len ,p->size());
#else
        int bytes_left = p->size ();
        int written_bytes;
        char* ptr = (char*) p->ptr();
        while (bytes_left > 0)
        {
            written_bytes = send (fd, ptr, bytes_left, 0);
            if (written_bytes <= 0) {
                if (errno == EINTR) {
                    if (written_bytes < 0) written_bytes = 0;
                    continue;
                }
                else if (errno == EAGAIN) {
                    if (written_bytes < 0) written_bytes = 0;
                    sleep (1);
                    continue;
                }
                else
                    break;
            }
            bytes_left -= written_bytes;
            ptr += written_bytes;
        }
#endif
        printf("Send data...finished. packetLength=%u, from FD=[%d]\n", p->size(), fd);

        p->reset();
        SINGLE->bufpool.free(p);
    }
    return 0;
}

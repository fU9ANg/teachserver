
#include "SendTask.h"
#include "Single.h"
#include "Buf.h"

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
            SINGLE->bufpool.free(p);
            continue;
        }

        int bytes_left = p->size ();
        int written_bytes;
        char* ptr = (char*) p->ptr();
        while (bytes_left > 0)
        {
            written_bytes = send (fd, ptr, bytes_left, 0);
            if (written_bytes <= 0) {
                if (errno == EINTR) {
                    if (written_bytes < 0) {
                        written_bytes = 0;
                        continue;
                    }
                }
                else if (errno == EAGAIN) {
                    if (written_bytes < 0) {
                        written_bytes = 0;
                        usleep (50);
                        continue;
                    }
                }
                else {
                    break;
                }
            }
            bytes_left -= written_bytes;
            ptr += written_bytes;
        }

        printf("Send data...finished. packetLength=%u, from FD=[%d]\n", p->size(), fd);

        p->reset();
        SINGLE->bufpool.free(p);
    }
    return 0;
}

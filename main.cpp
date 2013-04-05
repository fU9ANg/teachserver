/**
 * @ingroup framework
 * @{
 */
#include <stdio.h>
#include "ThreadPool.h"
#include "AtomicT.h"
#include "PoolT.h"
#include "Buf.h"

#include "ProcessManager.h"

int main(int argc, char* argv[]){
    ProcessManager* x = new ProcessManager();
    x->process_logic(argc, argv);
    delete x;
    return 0;
}
///@}

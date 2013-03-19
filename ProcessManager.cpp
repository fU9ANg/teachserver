#include "ProcessManager.h"
ProcessManager::ProcessManager() { thrpool_ = new ThreadPool(20);
}

ProcessManager::~ProcessManager() {
}

int ProcessManager::process_logic(int argc, char** argv) {
  signal(SIGINT, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTERM, sig_term);


  int opt = getopt(argc, argv, "uds");
  if ( -1 == opt) {
    printf("argv error\n");
    return -1;
  }
  int pid = 0;
  switch(opt){
    case 's':
      pid = fork();
      if(0 < pid){
        return 0;
      }
      if(true != lock(LOCK_NOWAIT)) {
        printf("Process already running!\n");
        return 0;
      } 
    case 'd':
      //初始化日志
      google::InitGoogleLogging(argv[0]);
      google::SetLogDestination(google::INFO, "./logs/info");
      google::SetLogDestination(google::WARNING, "./logs/warning");
      google::SetLogDestination(google::ERROR, "./logs/error");
      google::SetStderrLogging(google::ERROR + 1);
      //配置输出到标准错误的最低日志级别,使error日志不打屏
      system("mkdir -p logs");
      this->run();
      break;
    case 'u':
      if (true == lock(LOCK_NOWAIT))
      {   
        lock(UNLOCK);
        printf("No process!\n");
      } else {
        printf("Find process! stopping...\n");
        system("cat .lock|xargs kill -15");
      }  
      printf("stop\n");
      break;
    default:
      break;
  }


  return 0;
}

void ProcessManager::sig_term(int signo) {
  printf("get exit signal\n");
  LOG(INFO) << "server stoped";
  raise(SIGKILL);
  return;
}

int ProcessManager::run() {
  printf("run\n");

  LOG(INFO) << "server started";
  thrpool_->start();
  Evloop* evloop = new Evloop();
  RecvTask* p = new RecvTask();

  thrpool_->push_task(evloop);
  thrpool_->push_task(p);
  thrpool_->push_task(p);

  while (true) {
    sleep(3);
  }
  thrpool_->kill();
  return 0;
}

bool ProcessManager::lock(int mode) {
  char szPid[32] = {0};
  snprintf(szPid, 32, "%ld", (long)getpid());
  if (0 == lockfd_) {
    lockfd_ = open("./.lock", O_RDWR|O_CREAT, 0640);
  }
  if (lockfd_ < 0) {
    return false;
  }
  if (0 != flock(lockfd_, mode)) {
    return false;
  }
  if (UNLOCK == mode) {
    close(lockfd_);
  }
  else {
    ftruncate(lockfd_, 0); 
    write(lockfd_, szPid, strlen(szPid));
  }
  return true;
}


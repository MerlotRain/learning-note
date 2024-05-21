#include <iostream>
#include <wx/thread.h>
#include <wx/wx.h>

class MyThread : public wxThread {
public:
  MyThread() : wxThread(wxThreadKind::wxTHREAD_JOINABLE) {}
  ExitCode Entry() override {
    for (int i = 0; i < 10; ++i) {
      wxThread::Sleep(100);
      std::cout << i << std::endl;
      wxLogMessage(wxT("Hello world"));
    }
    return 0;
  }
};

int main(int argc, char **argv) {
  wxInitialize();
  MyThread *thread = new MyThread();
  if (thread->Create() != wxTHREAD_NO_ERROR) {
    wxLogError(wxT("create thread error"));
    return -1;
  }
  if (thread->Run() != wxTHREAD_NO_ERROR) {
    wxLogError(wxT("run error"));
    return -1;
  }
  thread->Wait();
  delete thread;
  return 0;
}
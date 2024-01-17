#ifndef __RTC_SERVER_H_
#define __RTC_SERVER_H_

#include <thread>

#include "base/event_loop.h"

namespace xrtc {
struct RtcServerOptions {
  int worker_num;
};

class RtcServer {
  enum {
    QUIT = 0,
    RTC_MSG = 1,
  };

 public:
  RtcServer();
  ~RtcServer();

  int init(const char *conf_file);
  bool start();
  void stop();
  int notify(int msg);
  void join();

  friend void rtc_server_recv_notify(EventLoop *el, IOWatcher *w, int fd,
                                     int events, void *data);

 private:
  void _process_notify(int msg);
  void _stop();

 private:
  EventLoop *_el;
  RtcServerOptions _options;

  std::thread *_thread = nullptr;

  IOWatcher *_pipe_watcher = nullptr;
  int _notify_recv_fd = -1;
  int _notify_send_fd = -1;
};
}  // namespace xrtc

#endif  // __RTC_SERVER_H_
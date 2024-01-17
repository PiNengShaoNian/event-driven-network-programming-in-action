#ifndef __RTC_WORKER_H_
#define __RTC_WORKER_H_

#include "rtc_server.h"

namespace xrtc {
class RtcWorker {
 public:
  RtcWorker(int worker_id, const RtcServerOptions &options);
  ~RtcWorker();

  int init();
  bool start();

  friend void rtc_worker_recv_notify(EventLoop *el, IOWatcher *w, int fd,
                                     int events, void *data);

 private:
  void _process_notify(int msg);

 private:
  RtcServerOptions _options;
  int _worker_id;
  EventLoop *_el;

  IOWatcher *_pipe_watcher = nullptr;
  int _notify_send_fd = -1;
  int _notify_recv_fd = -1;
};
}  // namespace xrtc

#endif  // __RTC_WORKER_H_
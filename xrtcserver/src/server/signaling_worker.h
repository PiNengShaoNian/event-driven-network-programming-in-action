#ifndef __SIGNALING_WORKER_H_
#define __SIGNALING_WORKER_H_

#include <thread>

#include "base/event_loop.h"

namespace xrtc {
class SignalingWorker {
 public:
  SignalingWorker(int worker_id);
  ~SignalingWorker();

  int init();
  bool start();
  void stop();

 private:
  int _worker_id;
  EventLoop *_el;
  IOWatcher *_pipe_watcher = nullptr;
  int _notify_recv_fd = -1;
  int _notify_send_fd = -1;
  std::thread *_thread = nullptr;
};
}  // namespace xrtc

#endif  // __SIGNALING_WORKER_H_
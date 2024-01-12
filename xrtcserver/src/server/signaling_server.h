#ifndef __SIGNALING_SERVER_H
#define __SIGNALING_SERVER_H

#include <string>
#include <thread>

#include "base/event_loop.h"

namespace xrtc {
struct SignalingServerOptions {
  std::string host;
  int port;
  int worker_num;
  int connection_timeout;
};

class SignalingServer {
 public:
  SignalingServer();
  ~SignalingServer();
  int init(const char *conf_file);
  bool start();
  void stop();

 private:
  SignalingServerOptions _options;
  EventLoop *_el;
  IOWatcher *_io_watcher = nullptr;
  IOWatcher *_pipe_watcher = nullptr;
  int _notify_recv_fd = -1;
  int _notify_send_fd = -1;
  std::thread *_thread = nullptr;

  int _listen_fd = -1;
};
}  // namespace xrtc

#endif  // __SIGNALING_SERVER_H
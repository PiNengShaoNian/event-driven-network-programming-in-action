#ifndef __SIGNALING_WORKER_H_
#define __SIGNALING_WORKER_H_

#include <rtc_base/slice.h>

#include <thread>
#include <vector>

#include "base/event_loop.h"
#include "base/lock_free_queue.h"
#include "json/json.h"
#include "signaling_server.h"

namespace xrtc {
class TcpConnection;

class SignalingWorker {
 public:
  enum {
    QUIT = 0,
    NEW_CONN = 1,
  };
  SignalingWorker(int worker_id, const SignalingServerOptions &options);
  ~SignalingWorker();

  int init();
  bool start();
  void stop();
  int notify(int msg);
  void join();
  int notify_new_conn(int fd);

  friend void signaling_worker_recv_notify(EventLoop *el, IOWatcher *w, int fd,
                                           int events, void *data);
  friend void conn_io_cb(EventLoop *el, IOWatcher *w, int fd, int events,
                         void *data);
  friend void conn_time_cb(EventLoop *el, TimerWatcher *w, void *data);

 private:
  void _process_notify(int msg);
  void _stop();
  void _new_conn(int fd);
  void _read_query(int fd);
  int _process_query_buffer(TcpConnection *c);
  int _process_request(TcpConnection *c, const rtc::Slice &header,
                       const rtc::Slice &body);
  void _close_conn(TcpConnection *c);
  void _remove_conn(TcpConnection *c);
  void _process_timeout(TcpConnection *c);
  int _process_push(int cmdno, TcpConnection *c, const Json::Value &root,
                    uint32_t log_id);

 private:
  int _worker_id;
  EventLoop *_el;
  SignalingServerOptions _options;
  IOWatcher *_pipe_watcher = nullptr;
  int _notify_recv_fd = -1;
  int _notify_send_fd = -1;
  std::thread *_thread = nullptr;
  LockFreeQueue<int> _q_conn;
  std::vector<TcpConnection *> _conns;
};
}  // namespace xrtc

#endif  // __SIGNALING_WORKER_H_
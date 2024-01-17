#include "rtc_worker.h"

#include <unistd.h>

#include "rtc_base/logging.h"

namespace xrtc {

void rtc_worker_recv_notify(EventLoop * /* el */, IOWatcher * /* w */, int fd,
                            int events, void *data) {}

RtcWorker::RtcWorker(int worker_id, const RtcServerOptions &options)
    : _options(options), _worker_id(worker_id), _el(new EventLoop(this)) {}

RtcWorker::~RtcWorker() {}

int RtcWorker::init() {
  int fds[2];
  if (pipe(fds)) {
    RTC_LOG(LS_WARNING) << "create pipe error: " << strerror(errno)
                        << ", errno: " << errno;
    return -1;
  }

  _notify_recv_fd = fds[0];
  _notify_send_fd = fds[1];
  _pipe_watcher = _el->create_io_event(rtc_worker_recv_notify, this);
  _el->start_io_event(_pipe_watcher, _notify_recv_fd, EventLoop::READ);

  return 0;
}

bool RtcWorker::start() { return true; }
}  // namespace xrtc

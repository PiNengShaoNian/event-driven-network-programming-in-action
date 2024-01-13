#include "signaling_worker.h"

#include <errno.h>
#include <unistd.h>

#include "rtc_base/logging.h"

namespace xrtc {
SignalingWorker::SignalingWorker(int worker_id)
    : _worker_id(worker_id), _el(new EventLoop(this)) {}

SignalingWorker::~SignalingWorker() {}

int SignalingWorker::init() {
  int fds[2];

  if (pipe(fds)) {
    RTC_LOG(LS_WARNING) << "create pipe error: " << strerror(errno)
                        << ", errno: " << errno;
  }

  return 0;
}
}  // namespace xrtc

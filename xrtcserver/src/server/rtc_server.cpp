#include "rtc_server.h"

#include <unistd.h>

#include "rtc_base/logging.h"
#include "yaml-cpp/yaml.h"

namespace xrtc {
void rtc_server_recv_notify(EventLoop * /* el */, IOWatcher * /* w */, int fd,
                            int events, void *data) {}

RtcServer::RtcServer() : _el(new EventLoop(this)) {}

RtcServer::~RtcServer() {}

int RtcServer::init(const char *conf_file) {
  if (!conf_file) {
    RTC_LOG(LS_WARNING) << "conf_file is null";
    return -1;
  }

  try {
    YAML::Node config = YAML::LoadFile(conf_file);
    RTC_LOG(LS_INFO) << "rtc server options:\n" << config;
    _options.worker_num = config["worker_num"].as<int>();
  } catch (YAML::Exception e) {
    RTC_LOG(LS_WARNING) << "rtc server load conf file error: " << e.msg;
    return -1;
  }

  int fds[2];
  if (pipe(fds)) {
    RTC_LOG(LS_WARNING) << "create pipe error" << strerror(errno)
                        << ", errno: " << errno;
    return -1;
  }

  _notify_recv_fd = fds[0];
  _notify_send_fd = fds[1];

  _pipe_watcher = _el->create_io_event(rtc_server_recv_notify, this);
  _el->start_io_event(_pipe_watcher, _notify_recv_fd, EventLoop::READ);

  return 0;
}

}  // namespace xrtc

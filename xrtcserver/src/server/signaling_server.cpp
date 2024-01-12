#include "signaling_server.h"

#include <unistd.h>

#include "base/socket.h"
#include "rtc_base/logging.h"
#include "yaml-cpp/yaml.h"

namespace xrtc {
void accept_new_conn(EventLoop *el, IOWatcher *w, int fd, int events,
                     void *data) {}

void signaling_server_recv_notify(EventLoop *el, IOWatcher *w, int fd,
                                  int events, void *data) {}

SignalingServer::SignalingServer() : _el(new EventLoop(this)) {}

SignalingServer::~SignalingServer() {}

int SignalingServer::init(const char *conf_file) {
  if (!conf_file) {
    RTC_LOG(LS_WARNING) << "singling server conf_file is null";
    return -1;
  }

  try {
    YAML::Node config = YAML::LoadFile(conf_file);
    RTC_LOG(LS_INFO) << "signaling server options:\n" << config;

    _options.host = config["host"].as<std::string>();
    _options.port = config["port"].as<int>();
    _options.worker_num = config["worker_num"].as<int>();
    _options.connection_timeout = config["connection_timeout"].as<int>();
  } catch (const YAML::Exception &e) {
    RTC_LOG(LS_WARNING) << "catch a YAML exception, line: " << e.mark.line + 1
                        << ", column: " << e.mark.column + 1
                        << ", error: " << e.msg;
    return -1;
  }

  // 创建管道用于线程间通信
  int fds[2];
  if (pipe(fds)) {
    RTC_LOG(LS_WARNING) << "create pipe error: " << strerror(errno)
                        << ", errno: " << errno;
    return -1;
  }

  _notify_recv_fd = fds[0];
  _notify_send_fd = fds[1];
  // 将recv_fd添加到事件循环进行管理
  _pipe_watcher = _el->create_io_event(signaling_server_recv_notify, this);
  _el->start_io_event(_pipe_watcher, _notify_recv_fd, EventLoop::READ);

  // 创建tcp server
  _listen_fd = create_tcp_server(_options.host.c_str(), _options.port);
  _io_watcher = _el->create_io_event(accept_new_conn, this);
  _el->start_io_event(_io_watcher, _listen_fd, EventLoop::READ);

  return 0;
}

bool SignalingServer::start() {
  if (_thread) {
    RTC_LOG(LS_WARNING) << "signaling server already start";
    return false;
  }

  _thread = new std::thread([=]() {
    RTC_LOG(LS_INFO) << "signaling server event loop run";
    _el->start();
    RTC_LOG(LS_INFO) << "signaling server event loop stop";
  });

  return true;
}

void SignalingServer::stop() {}
}  // namespace xrtc
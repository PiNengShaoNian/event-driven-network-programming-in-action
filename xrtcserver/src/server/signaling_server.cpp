#include "signaling_server.h"

#include "rtc_base/logging.h"
#include "yaml-cpp/yaml.h"

namespace xrtc {
SignalingServer::SignalingServer() {}

SignalingServer::~SignalingServer() {}

int SignalingServer::init(const char* conf_file) {
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
  } catch (const YAML::Exception& e) {
    RTC_LOG(LS_WARNING) << "catch a YAML exception, line: " << e.mark.line + 1
                        << ", column: " << e.mark.column + 1
                        << ", error: " << e.msg;
    return -1;
  }

  return 0;
}
}  // namespace xrtc
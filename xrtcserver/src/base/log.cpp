#include "log.h"

#include <iostream>

namespace xrtc {

XrtcLog::XrtcLog(const std::string &log_dir, const std::string &log_name,
                 const std::string &log_level)
    : _log_dir(log_dir), _log_name(log_name), _log_level(log_level) {}

XrtcLog::~XrtcLog() {}

void XrtcLog::OnLogMessage(const std::string &message,
                           rtc::LoggingSeverity severity) {
  std::cout << "OnLogMessage: " << message << std::endl;
}

void XrtcLog::OnLogMessage(const std::string & /*message*/) {}

static rtc::LoggingSeverity get_log_severity(const std::string &level) {
  if (level == "verbose") {
    return rtc::LoggingSeverity::LS_VERBOSE;
  }
  if (level == "info") {
    return rtc::LoggingSeverity::LS_INFO;
  }
  if (level == "warning") {
    return rtc::LoggingSeverity::LS_WARNING;
  }
  if (level == "error") {
    return rtc::LoggingSeverity::LS_ERROR;
  }

  return rtc::LoggingSeverity::LS_NONE;
}

int XrtcLog::init() {
  rtc::LogMessage::ConfigureLogging("thread tstamp");
  rtc::LogMessage::SetLogPathPrefix("/src");
  rtc::LogMessage::AddLogToStream(this, get_log_severity(_log_level));
  return 0;
}

void XrtcLog::set_log_to_stderr(bool on) {
  rtc::LogMessage::SetLogToStderr(on);
}
}  // namespace xrtc
#include "log.h"

#include <sys/stat.h>

#include <iostream>

namespace xrtc {

XrtcLog::XrtcLog(const std::string &log_dir, const std::string &log_name,
                 const std::string &log_level)
    : _log_dir(log_dir),
      _log_name(log_name),
      _log_level(log_level),
      _log_file(log_dir + "/" + log_name + ".log"),
      _log_file_wf(log_dir + "/" + log_name + ".log.wf") {}

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

  int ret = mkdir(_log_dir.c_str(), 0755);
  if (ret != 0 && errno != EEXIST) {
    fprintf(stderr, "create log_dir[%s] failed\n", _log_dir.c_str());
    return -1;
  }

  // 打开文件
  _out_file.open(_log_file, std::ios::app);
  if (!_out_file.is_open()) {
    fprintf(stderr, "open log_file[%s] failed\n", _log_file.c_str());
    return -1;
  }

  _out_file_wf.open(_log_file_wf, std::ios::app);
  if (!_out_file_wf.is_open()) {
    fprintf(stderr, "open log_file[%s] failed\n", _log_file_wf.c_str());
    _out_file.close();
    return -1;
  }

  return 0;
}

void XrtcLog::set_log_to_stderr(bool on) {
  rtc::LogMessage::SetLogToStderr(on);
}
}  // namespace xrtc
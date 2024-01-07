#include "log.h"

namespace xrtc {

XrtcLog::XrtcLog(const std::string &log_dir, const std::string &log_name,
                 const std::string &log_level)
    : _log_dir(log_dir), _log_name(log_name), _log_level(log_level) {}

XrtcLog::~XrtcLog() {}

void XrtcLog::OnLogMessage(const std::string &message,
                           rtc::LoggingSeverity severity) {}

void XrtcLog::OnLogMessage(const std::string & /*message*/) {}

int XrtcLog::init() { rtc::LogMessage::AddLogToStream(this, rtc::LS_INFO); }
}  // namespace xrtc
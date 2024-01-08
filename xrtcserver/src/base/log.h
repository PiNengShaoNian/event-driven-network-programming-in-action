#ifndef __BASE_LOG_H
#define __BASE_LOG_H

#include "rtc_base/logging.h"

namespace xrtc {
class XrtcLog : public rtc::LogSink {
 public:
  XrtcLog(const std::string &log_dir, const std::string &log_name,
          const std::string &log_level);
  ~XrtcLog() override;

  void OnLogMessage(const std::string &message,
                    rtc::LoggingSeverity severity) override;
  void OnLogMessage(const std::string &message) override;

  int init();
  void set_log_to_stderr(bool on);

 private:
  std::string _log_dir;
  std::string _log_name;
  std::string _log_level;
};
}  // namespace xrtc

#endif  //__BASE_LOG_H
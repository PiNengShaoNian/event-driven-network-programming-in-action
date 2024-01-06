#include "conf.h"

#include <stdio.h>

namespace xrtc {
int load_general_conf(const char *filename, GeneralConf *conf) {
  if (!filename || !conf) {
    fprintf(stderr, "filename or conf is nullptr\n");
    return -1;
  }

  conf->log_dir = "./log";
  conf->log_name = "undefined";
  conf->log_level = "info";
  conf->log_to_stderr = false;

  return 0;
}
}  // namespace xrtc
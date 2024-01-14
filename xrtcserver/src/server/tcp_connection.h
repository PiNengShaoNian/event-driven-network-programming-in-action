#ifndef __TCP_CONNECTION_H_
#define __TCP_CONNECTION_H_

namespace xrtc {
class TcpConnection {
 public:
  TcpConnection(int fd);
  ~TcpConnection();

 public:
  int fd;
  char ip[64];
  int port;
};
}  // namespace xrtc

#endif  // __TCP_CONNECTION_H_
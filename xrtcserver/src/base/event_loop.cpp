#include "event_loop.h"

#include "libev/ev.h"

#define TRANS_TO_EV_MASK(mask)                \
  (((mask & EventLoop::READ) ? EV_READ : 0) | \
   ((mask & EventLoop::WRITE) ? EV_WRITE : 0))

#define TRANS_FROM_EV_MASK(mask)              \
  (((mask & EV_READ) ? EventLoop::READ : 0) | \
   ((mask & EV_WRITE) ? EventLoop::WRITE : 0))

namespace xrtc {
EventLoop::EventLoop(void *owner)
    : _owner(owner), _loop(ev_loop_new(EVFLAG_AUTO)) {}

EventLoop::~EventLoop() {}

class IOWatcher {
 public:
  EventLoop *el;
  ev_io io;
  io_cb_t cb;
  void *data;

  IOWatcher(EventLoop *el, io_cb_t cb, void *data)
      : el(el), cb(cb), data(data) {
    io.data = this;
  }
};

static void generic_io_cb(struct ev_loop * /* loop */, struct ev_io *io,
                          int events) {
  IOWatcher *watcher = (IOWatcher *)io->data;
  watcher->cb(watcher->el, watcher, io->fd, TRANS_FROM_EV_MASK(events),
              watcher->data);
}

IOWatcher *EventLoop::create_io_event(io_cb_t cb, void *data) {
  IOWatcher *w = new IOWatcher(this, cb, data);
  ev_init(&(w->io), generic_io_cb);
  return w;
}

void EventLoop::start() { ev_run(_loop); }
void EventLoop::stop() { ev_break(_loop, EVBREAK_ALL); }
}  // namespace xrtc

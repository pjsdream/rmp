#ifndef RMP_RENDERER_OSTREAM_H
#define RMP_RENDERER_OSTREAM_H

#include <rmp/comm/publisher.h>
#include <rmp/utils/timer.h>

namespace rmp
{
class RendererOstream
{
public:
  RendererOstream()
      : publisher_("renderer", "127.0.0.1"), created_timer_(0.1)
  {
  }

  template<typename T>
  RendererOstream& operator<<(T&& request)
  {
    created_timer_.sleepUntil();
    publisher_ << request.type() << std::forward<T>(request);
    return *this;
  }

  void flush()
  {
    publisher_.flush();
  }

private:
  Timer created_timer_;
  Publisher publisher_;
};
}

#endif //RMP_RENDERER_OSTREAM_H

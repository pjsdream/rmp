#ifndef RMP_REQUEST_FRAME_ATTACH_H
#define RMP_REQUEST_FRAME_ATTACH_H

#include <string>

#include "request.h"

namespace rmp
{
class RequestFrameAttach : public Request
{
public:
  RequestFrameAttach()
      : Request(Request::Type::FrameAttach)
  {
  }

  template<typename Archive>
  Archive& serialize(Archive& ar)
  {
    return ar & frame & resource;
  }

  std::string frame;
  std::string resource;

private:
};
}

#endif //RMP_REQUEST_FRAME_ATTACH_H

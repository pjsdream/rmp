#ifndef RMP_REQUEST_CLEAR_H
#define RMP_REQUEST_CLEAR_H

#include "request.h"

namespace rmp
{
class RequestClear : public Request
{
public:
  RequestClear() : Request(Request::Type::Clear)
  {
  }

  template<typename Archive>
  Archive& serialize(Archive& ar)
  {
    return ar;
  }
};
}

#endif //RMP_REQUEST_CLEAR_H

#ifndef RMP_REQUEST_FRAME_H
#define RMP_REQUEST_FRAME_H

#include <Eigen/Dense>

#include "request.h"

namespace rmp
{
class RequestFrame : public Request
{
public:
  RequestFrame()
      : Request(Request::Type::Frame), transform(Eigen::Affine3d::Identity())
  {
  }

  ~RequestFrame() override = default;

  enum class Action
  {
    Nothing,
    Set,
    Delete,
  };

  template<typename Archive>
  Archive& serialize(Archive& ar)
  {
    return ar & action & name & parent & transform;
  }

  Action action;
  std::string name;
  std::string parent;
  Eigen::Affine3d transform;
};
}

#endif //RMP_REQUEST_FRAME_H

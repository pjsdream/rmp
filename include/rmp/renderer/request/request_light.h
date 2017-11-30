#ifndef RMP_REQUEST_LIGHT_H
#define RMP_REQUEST_LIGHT_H

#include <Eigen/Dense>

#include "request.h"

namespace rmp
{
class RequestLight : public Request
{
public:
  enum class Action : unsigned char
  {
    Nothing,
    Set,
    Delete,
  };

  enum class LightType : unsigned char
  {
    Directional,
    Point
  };

  RequestLight()
      : Request(Request::Type::Light)
  {
  }

  ~RequestLight() override = default;

  template<typename Archive>
  Archive& serialize(Archive& ar)
  {
    return ar & action & index & light_type & position & ambient & diffuse & specular & attenuation;
  }

  Action action = Action::Nothing;
  int index = 0;
  LightType light_type = LightType::Directional;
  Eigen::Vector3f position;
  Eigen::Vector3f ambient;
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
  Eigen::Vector3f attenuation;
};
}

#endif //RMP_REQUEST_LIGHT_H

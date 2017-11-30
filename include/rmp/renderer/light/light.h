#ifndef RMP_LIGHT_H
#define RMP_LIGHT_H

#include <Eigen/Dense>

namespace rmp
{
struct Light
{
  enum class LightType
  {
    Directional,
    Point
  };

  LightType type;
  Eigen::Vector3f position;
  Eigen::Vector3f ambient;
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
  Eigen::Vector3f attenuation;
};
}

#endif //RMP_LIGHT_H

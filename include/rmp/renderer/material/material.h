#ifndef RMP_MATERIAL_H
#define RMP_MATERIAL_H

#include <Eigen/Dense>

namespace rmp
{
struct Material
{
  Eigen::Vector3f ambient;
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
  float shininess;
};
}

#endif //RMP_MATERIAL_H

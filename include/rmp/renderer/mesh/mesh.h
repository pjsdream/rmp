#ifndef RMP_MESH_H
#define RMP_MESH_H

#include <vector>

#include <Eigen/Dense>

#include <rmp/renderer/material/material.h>

namespace rmp
{
struct Mesh
{
  std::vector<float> vertex_buffer;
  std::vector<float> normal_buffer;
  std::vector<float> texture_buffer;
  std::vector<float> color_buffer;
  std::vector<int> face_buffer;

  bool has_global_color;
  Eigen::Vector3f global_color;

  std::string texture_filename;

  Material material;
};
}

#endif //RMP_MESH_H

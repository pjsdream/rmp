#ifndef RMP_MESH_LOADER_H
#define RMP_MESH_LOADER_H

#include <future>
#include <string>

#include <rmp/renderer/mesh/mesh.h>

namespace rmp
{
class MeshLoader
{
public:
  MeshLoader() = delete;
  explicit MeshLoader(const std::string& filename);

  bool ready();
  Mesh get();

private:
  static std::string getDirectory(const std::string& filename);

  std::future<Mesh> future_mesh_;
};
}

#endif //RMP_MESH_LOADER_H

#ifndef RMP_RESOURCE_MESH_H
#define RMP_RESOURCE_MESH_H

#include <Eigen/Dense>

#include <rmp/renderer/gl_base.h>
#include <rmp/renderer/mesh/mesh.h>
#include <rmp/renderer/resource/resource_texture.h>
#include <rmp/renderer/mesh/mesh_loader.h>

namespace rmp
{
class ResourceMesh : public GlBase
{
public:
  ResourceMesh() = delete;
  explicit ResourceMesh(const std::shared_ptr<GlFunctions>& gl);
  ~ResourceMesh() override;

  void loadMesh(Mesh&& mesh);
  void loadMesh(const std::string& filename);

  bool hasTexture();
  std::shared_ptr<ResourceTexture> getTexture();
  void setTexture(const std::shared_ptr<ResourceTexture>& texture);

  bool hasColor();

  bool hasGlobalColor();
  const Eigen::Vector3f& getGlobalColor();

  void draw();

private:
  enum class ColorOption
  {
    Texture,
    Color,
    GlobalColor,
  };
  ColorOption color_option_;

  std::unique_ptr<MeshLoader> loader_;

  GLuint vao_ = 0;
  std::vector<GLuint> vbos_;
  unsigned int num_faces_;

  std::shared_ptr<ResourceTexture> texture_;
  Eigen::Vector3f global_color_;
};
}

#endif //RMP_RESOURCE_MESH_H

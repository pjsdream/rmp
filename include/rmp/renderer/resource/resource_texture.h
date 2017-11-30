#ifndef RMP_RESOURCE_TEXTURE_H
#define RMP_RESOURCE_TEXTURE_H

#include <string>

#include <rmp/renderer/gl_base.h>
#include <rmp/renderer/texture/texture.h>
#include <rmp/renderer/texture/texture_loader.h>

namespace rmp
{
class ResourceTexture : public GlBase
{
public:
  ResourceTexture() = delete;
  explicit ResourceTexture(const std::shared_ptr<GlFunctions>& gl);

  ~ResourceTexture() override;

  void loadTexture(Texture&& texture);
  void loadTexture(const std::string& filename);

  void bind();

private:
  GLuint texture_id_ = 0;

  std::unique_ptr<TextureLoader> loader_;
};
}

#endif //RMP_RESOURCE_TEXTURE_H

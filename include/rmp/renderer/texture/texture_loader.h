#ifndef RMP_TEXTURE_LOADER_H
#define RMP_TEXTURE_LOADER_H

#include <string>
#include <future>

#include "texture.h"

namespace rmp
{
class TextureLoader
{
public:
  TextureLoader() = delete;
  explicit TextureLoader(const std::string& filename);

  bool ready();
  Texture get();

private:
  std::future<Texture> future_texture_;
};
}

#endif //RMP_TEXTURE_LOADER_H

#include <rmp/renderer/texture/texture_loader.h>
#include <lib/lodepng/lodepng.h>

namespace rmp
{
TextureLoader::TextureLoader(const std::string& filename)
{
  future_texture_ = std::async(std::launch::async, [filename](){
    Texture texture;
    lodepng::decode(texture.image, texture.width, texture.height, filename.c_str());
    return texture;
  });
}

bool TextureLoader::ready()
{
  using namespace std::literals::chrono_literals;
  return future_texture_.valid() && future_texture_.wait_for(0s) == std::future_status::ready;
}

Texture TextureLoader::get()
{
  return future_texture_.get();
}
}

#ifndef RMP_TEXTURE_H
#define RMP_TEXTURE_H

#include <vector>

namespace rmp
{
struct Texture
{
  unsigned int width;
  unsigned int height;
  std::vector<unsigned char> image;
};
}

#endif //RMP_TEXTURE_H

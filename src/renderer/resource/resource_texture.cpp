#include <rmp/renderer/resource/resource_texture.h>

namespace rmp
{
ResourceTexture::ResourceTexture(const std::shared_ptr<GlFunctions>& gl)
    : GlBase(gl)
{
}

ResourceTexture::~ResourceTexture()
{
  if (texture_id_ != 0)
    gl_->glDeleteTextures(1, &texture_id_);
}

void ResourceTexture::loadTexture(Texture&& texture)
{
  gl_->glGenTextures(1, &texture_id_);
  gl_->glBindTexture(GL_TEXTURE_2D, texture_id_);
  gl_->glTexImage2D(GL_TEXTURE_2D,
                    0,
                    GL_RGB,
                    texture.width,
                    texture.height,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    &texture.image[0]);
  gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  gl_->glBindTexture(GL_TEXTURE_2D, 0);
}

void ResourceTexture::loadTexture(const std::string& filename)
{
  loader_ = std::make_unique<TextureLoader>(filename);
}

void ResourceTexture::bind()
{
  if (loader_)
  {
    if (loader_->ready())
    {
      loadTexture(loader_->get());
      loader_.release();
    }
  }

  gl_->glBindTexture(GL_TEXTURE_2D, texture_id_);
}
}

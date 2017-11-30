#include <rmp/renderer/resource/resource_mesh.h>

namespace rmp
{
ResourceMesh::ResourceMesh(const std::shared_ptr<GlFunctions>& gl)
    : GlBase(gl),
      color_option_(ColorOption::GlobalColor),
      global_color_(Eigen::Vector3f(0.8f, 0.8f, 0.8f))
{
}

ResourceMesh::~ResourceMesh()
{
  if (vao_ != 0)
    gl_->glDeleteVertexArrays(1, &vao_);

  gl_->glDeleteBuffers(5, &vbos_[0]);
}

void ResourceMesh::draw()
{
  using namespace std::literals::chrono_literals;

  if (loader_)
  {
    if (!loader_->ready())
      return;

    loadMesh(loader_->get());
    loader_.release();
  }

  gl_->glBindVertexArray(vao_);
  gl_->glDrawElements(GL_TRIANGLES, num_faces_ * 3, GL_UNSIGNED_INT, 0);
  gl_->glBindVertexArray(0);
}

void ResourceMesh::loadMesh(Mesh&& mesh)
{
  gl_->glGenVertexArrays(1, &vao_);

  vbos_.resize(5);
  gl_->glGenBuffers(5, &vbos_[0]);

  gl_->glBindVertexArray(vao_);
  gl_->glBindBuffer(GL_ARRAY_BUFFER, vbos_[0]);
  gl_->glBufferData(GL_ARRAY_BUFFER,
                    sizeof(float) * mesh.vertex_buffer.size(),
                    &mesh.vertex_buffer[0],
                    GL_STATIC_DRAW);
  gl_->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  gl_->glEnableVertexAttribArray(0);

  gl_->glBindBuffer(GL_ARRAY_BUFFER, vbos_[1]);
  gl_->glBufferData(GL_ARRAY_BUFFER,
                    sizeof(float) * mesh.normal_buffer.size(),
                    &mesh.normal_buffer[0],
                    GL_STATIC_DRAW);
  gl_->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  gl_->glEnableVertexAttribArray(1);

  if (!mesh.texture_buffer.empty())
  {
    // will be changed to texture when it is loaded
    color_option_ = ColorOption::GlobalColor;

    gl_->glBindBuffer(GL_ARRAY_BUFFER, vbos_[2]);
    gl_->glBufferData(GL_ARRAY_BUFFER,
                      sizeof(float) * mesh.texture_buffer.size(),
                      &mesh.texture_buffer[0],
                      GL_STATIC_DRAW);
    gl_->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    gl_->glEnableVertexAttribArray(2);

    // load texture
    if (!mesh.texture_filename.empty())
    {
      color_option_ = ColorOption::Texture;
      texture_ = std::make_shared<ResourceTexture>(gl_);
      texture_->loadTexture(mesh.texture_filename);
    }
  }

  else if (!mesh.color_buffer.empty())
  {
    // TODO: mesh that has both texture and color
    color_option_ = ColorOption::Color;

    gl_->glBindBuffer(GL_ARRAY_BUFFER, vbos_[3]);
    gl_->glBufferData(GL_ARRAY_BUFFER,
                      sizeof(float) * mesh.color_buffer.size(),
                      &mesh.color_buffer[0],
                      GL_STATIC_DRAW);
    gl_->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    gl_->glEnableVertexAttribArray(3);
  }

  else if (mesh.has_global_color)
  {
    color_option_ = ColorOption::GlobalColor;
    global_color_ = mesh.global_color;
  }

  else
  {
    color_option_ = ColorOption::GlobalColor;
  }

  gl_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos_[4]);
  gl_->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                    sizeof(int) * mesh.face_buffer.size(),
                    &mesh.face_buffer[0],
                    GL_STATIC_DRAW);

  gl_->glBindVertexArray(0);
  gl_->glBindBuffer(GL_ARRAY_BUFFER, 0);
  gl_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  num_faces_ = mesh.face_buffer.size() / 3;
}

void ResourceMesh::loadMesh(const std::string& filename)
{
  loader_ = std::make_unique<MeshLoader>(filename);
}

bool ResourceMesh::hasTexture()
{
  return color_option_ == ColorOption::Texture;
}

std::shared_ptr<ResourceTexture> ResourceMesh::getTexture()
{
  return texture_;
}

void ResourceMesh::setTexture(const std::shared_ptr<ResourceTexture>& texture)
{
  color_option_ = ColorOption::Texture;
  texture_ = texture;
}

bool ResourceMesh::hasColor()
{
  return color_option_ == ColorOption::Color;
}

bool ResourceMesh::hasGlobalColor()
{
  return color_option_ == ColorOption::GlobalColor;
}

const Eigen::Vector3f& ResourceMesh::getGlobalColor()
{
  return global_color_;
}
}

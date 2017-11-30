#ifndef RMP_GL_BASE_H
#define RMP_GL_BASE_H

#include <memory>

#include <QOpenGLFunctions_4_1_Core>

namespace rmp
{
using GlFunctions = QOpenGLFunctions_4_1_Core;

class GlBase
{
public:
  GlBase() = delete;
  explicit GlBase(const std::shared_ptr<GlFunctions>& gl)
  {
    gl_ = gl;
  }

  virtual ~GlBase() = default;

protected:
  std::shared_ptr<GlFunctions> gl_;
};
}

#endif //RMP_GL_BASE_H

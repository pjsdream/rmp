#ifndef RMP_LIGHT_SHADER_H
#define RMP_LIGHT_SHADER_H

#include "shader.h"

#include <rmp/renderer/camera/camera.h>
#include <rmp/renderer/light/light.h>
#include <rmp/renderer/material/material.h>
#include <rmp/renderer/texture/texture.h>

namespace rmp
{
class LightShader : public Shader
{
public:
  explicit LightShader(const std::shared_ptr<GlFunctions>& gl);

  void loadModel(const Eigen::Affine3d& model);
  void loadView(const Eigen::Affine3d& view);
  void loadView(const Eigen::Matrix4d& view);
  void loadProjection(const Eigen::Affine3d& projection);
  void loadProjection(const Eigen::Matrix4d& projection);
  void loadCamera(const std::shared_ptr<Camera>& camera);

  void loadLight(int index, const std::shared_ptr<Light>& light);
  void loadMaterial(const std::shared_ptr<Material>& material);

  void hasTexture(const std::shared_ptr<Texture>& texture);
  void hasColor();
  void hasGlobalColor(const Eigen::Vector3f& color);

private:
  static const int NUM_LIGHTS = 8;

  enum class ColorOption
  {
    Texture,
    Color,
    GlobalColor,
  };

  void setUniformLocations();

  ColorOption color_option_;

  GLint loc_model_;
  GLint loc_projection_;
  GLint loc_view_;
  GLint loc_model_inverse_transpose_;

  GLint loc_eye_position_;

  GLint loc_has_texture_;
  GLint loc_has_color_;
  GLint loc_has_global_color_;
  GLint loc_global_color_;

  struct LocLight
  {
    GLint use;
    GLint type;
    GLint position;
    GLint ambient;
    GLint diffuse;
    GLint specular;
    GLint attenuation;
  };
  LocLight loc_lights_[NUM_LIGHTS];

  struct LocMaterial
  {
    GLint ambient;
    GLint diffuse;
    GLint specular;
    GLint shininess;
  };
  LocMaterial loc_material_;

  GLint loc_has_material_;
  GLint loc_material_texture_;
};
}

#endif //RMP_LIGHT_SHADER_H

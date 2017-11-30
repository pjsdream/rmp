#ifndef RMP_CAMERA_H
#define RMP_CAMERA_H

#include <Eigen/Dense>

namespace rmp
{
class Camera
{
private:
  enum class ProjectionType
  {
    Ortho,
    Perspective,
  };

public:
  Camera();

  void setAspect(double aspect);
  void setFovy(double fovy);
  void setPerspective();
  void setOrtho();
  void setSensitivityTranslation(double sensitivity);
  void setSensitivityZoom(double sensitivity);
  void setNear(double n);
  void setFar(double f);

  void lookAt(const Eigen::Vector3d& eye, const Eigen::Vector3d& center);
  void lookAt(const Eigen::Vector3d& eye, const Eigen::Vector3d& center, const Eigen::Vector3d& up);

  void translatePixel(int dx, int dy);
  void rotatePixel(int dx, int dy);
  void zoomPixel(int dx, int dy);

  Eigen::Matrix4d projectionMatrix() const;
  Eigen::Matrix4d viewMatrix() const;

  inline const Eigen::Vector3d& eyePosition() const
  {
    return eye_;
  }

  inline Eigen::Vector3d lookAtDirection() const
  {
    return (center_ - eye_).normalized();
  }

private:
  Eigen::Matrix4d perspective() const;
  Eigen::Matrix4d ortho() const;

  ProjectionType projection_type_;

  double fovy_;
  double aspect_;
  double near_;
  double far_;

  Eigen::Vector3d eye_;
  Eigen::Vector3d center_;
  Eigen::Vector3d up_;

  double sensitivity_translation_;
  double sensitivity_rotation_;
  double sensitivity_zoom_;
};
}

#endif //RMP_CAMERA_H

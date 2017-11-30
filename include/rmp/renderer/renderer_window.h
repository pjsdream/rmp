#ifndef RMP_RENDERER_WINDOW_H
#define RMP_RENDERER_WINDOW_H

#include <memory>
#include <unordered_map>

#include <QOpenGLWindow>
#include <QMouseEvent>
#include <Eigen/Dense>

#include <rmp/comm/subscriber.h>
#include <rmp/renderer/request/requests.h>
#include <rmp/renderer/gl_base.h>
#include <rmp/renderer/camera/camera.h>
#include <rmp/renderer/shader/light_shader.h>

namespace rmp
{
class RendererWindow : public QOpenGLWindow
{
Q_OBJECT

public:
  RendererWindow();
  ~RendererWindow() override;

  RendererWindow(const RendererWindow& rhs) = delete;
  RendererWindow& operator=(const RendererWindow& rhs) = delete;

  RendererWindow(RendererWindow&& rhs) = delete;
  RendererWindow& operator=(RendererWindow&& rhs) = delete;

protected:
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void initializeGL() override;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

private:
  bool receiveRequest();
  void receiveRequests();
  void handleRequests();

  std::shared_ptr<GlFunctions> gl_;

  Subscriber request_subscriber_;
  std::vector<std::unique_ptr<Request>> requests_;

  std::shared_ptr<LightShader> light_shader_;

  std::shared_ptr<Camera> camera_;

  int last_mouse_x_;
  int last_mouse_y_;
};
}

#endif //RMP_RENDERER_WINDOW_H

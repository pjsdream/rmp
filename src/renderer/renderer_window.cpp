#include <rmp/renderer/renderer_window.h>

#include <iostream>

#include <QTimer>

namespace rmp
{
//
// RendererWindow::Impl
//
RendererWindow::RendererWindow()
    : camera_(std::make_unique<Camera>()),
      request_subscriber_("renderer", "127.0.0.1")
{
}

RendererWindow::~RendererWindow() = default;

bool RendererWindow::receiveRequest()
{
  if (request_subscriber_.eof())
    return false;

  Request::Type type;
  request_subscriber_ >> type;

  printf("type: %d\n", static_cast<int>(type));

  switch (type)
  {
    case Request::Type::Clear:
    {
      auto req = std::make_unique<RequestClear>();
      request_subscriber_ >> *req;
      std::cout << "Clear\n";
      requests_.push_back(std::move(req));
    }
      break;

    case Request::Type::Mesh:
    {
      auto req = std::make_unique<RequestMesh>();
      request_subscriber_ >> *req;

      std::cout << "Mesh name: " << req->name << ", filename: " << req->filename << "\n";
      requests_.push_back(std::move(req));
    }
      break;

    case Request::Type::CustomMesh:
    {
      /*
      auto req = std::make_unique<RequestCustomMesh>();
      request_subscriber_ >> *req;

      std::cout << "Custom Mesh name: " << req->name << ", # vertices: " << req->vertex_buffer.size() << "\n";
      requests_.push_back(std::move(req));
       */
    }
      break;

    case Request::Type::CustomTexture:
    {
      /*
      auto req = std::make_unique<RequestCustomTexture>();
      request_subscriber_ >> *req;

      std::cout << "Custom Texture name: " << req->name << ", size = (" << req->w << ", " << req->h << ")\n";
      requests_.push_back(std::move(req));
       */
    }
      break;

    case Request::Type::Light:
    {
      auto req = std::make_unique<RequestLight>();
      request_subscriber_ >> *req;

      std::cout << "Light action: " << static_cast<int>(req->action) << ", index: " << req->index << "\n";
      requests_.push_back(std::move(req));
    }
      break;

    case Request::Type::Frame:
    {
      auto req = std::make_unique<RequestFrame>();
      request_subscriber_ >> *req;

      std::cout << "Frame name: " << req->name << ", parent: " << req->parent << ", transform:\n"
                << req->transform.matrix() << "\n";
      requests_.push_back(std::move(req));
    }
      break;

    case Request::Type::FrameAttach:
    {
      auto req = std::make_unique<RequestFrameAttach>();
      request_subscriber_ >> *req;

      std::cout << "Frame Attach frame: " << req->frame << ", resource: " << req->resource << "\n";
      requests_.push_back(std::move(req));
    }
      break;
  }

  return true;
}

void RendererWindow::receiveRequests()
{
  requests_.clear();
  while (receiveRequest());
}

void RendererWindow::handleRequests()
{
}

void RendererWindow::paintGL()
{
  gl_->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TODO: Update scene upon requests
  receiveRequests();
  handleRequests();

  // TODO: draw objects
  light_shader_->start();
  light_shader_->end();
}

void RendererWindow::resizeGL(int w, int h)
{
  gl_->glViewport(0, 0, w, h);
  camera_->setAspect((double) w / h);

  update();
}

void RendererWindow::initializeGL()
{
  auto deleter = [](GlFunctions*)
  {};
  gl_.reset(context()->versionFunctions<GlFunctions>(), deleter);

  gl_->glClearColor(0.8f, 0.8f, 0.8f, 0.f);
  gl_->glEnable(GL_DEPTH_TEST);
  gl_->glEnable(GL_MULTISAMPLE);

  // shaders
  light_shader_ = std::make_shared<LightShader>(gl_);

  // animation
  QTimer* timer = new QTimer(this);
  timer->setInterval(16);
  connect(timer, SIGNAL(timeout()), this, SLOT(requestUpdate()));
  timer->start();
}

void RendererWindow::mousePressEvent(QMouseEvent* event)
{
  last_mouse_x_ = event->x();
  last_mouse_y_ = event->y();
}

void RendererWindow::mouseMoveEvent(QMouseEvent* event)
{
  const int x = event->x();
  const int y = event->y();
  const int dx = x - last_mouse_x_;
  const int dy = y - last_mouse_y_;

  last_mouse_x_ = x;
  last_mouse_y_ = y;

  switch (event->buttons())
  {
    case Qt::LeftButton:
      camera_->rotatePixel(dx, dy);
      requestUpdate();
      break;

    case Qt::RightButton:
      camera_->translatePixel(dx, dy);
      requestUpdate();
      break;

    case Qt::LeftButton | Qt::RightButton:
      camera_->zoomPixel(dx, dy);
      requestUpdate();
      break;
  }
}
}

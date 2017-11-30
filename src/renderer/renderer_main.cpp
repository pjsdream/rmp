#include <rmp/renderer/renderer_window.h>

#include <QApplication>

int main(int argc, char** argv)
{
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);

  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setSamples(4);
  format.setVersion(4, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  // renderer
  auto renderer_window = std::make_shared<rmp::RendererWindow>();

  // showing renderer
  renderer_window->resize(800, 600);
  renderer_window->show();

  app.exec();

  renderer_window.reset();
  return 0;
}

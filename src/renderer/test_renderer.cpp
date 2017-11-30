#include <rmp/renderer/renderer.h>

#include <iostream>

int main()
{
  rmp::RendererOstream rout;

  rmp::RequestClear clear;
  rout << clear;
  rout.flush();

  return 0;
}

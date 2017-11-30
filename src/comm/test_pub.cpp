#include <rmp/comm/publisher.h>

#include <iostream>
#include <thread>
#include <chrono>

int main()
{
  std::cout << "Testing publisher\n";

  rmp::Publisher publisher("testing_topic", "127.0.0.1");

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(50ms);

  std::cout << "[" << std::chrono::high_resolution_clock::now().time_since_epoch().count() << "] preparing publish\n";
  for (int i=0; i<100; i++)
  {
    auto d = static_cast<double>(i);

    publisher << d;
  }
  publisher.flush();
  std::cout << "[" << std::chrono::high_resolution_clock::now().time_since_epoch().count() << "] publishing complete\n";

  return 0;
}

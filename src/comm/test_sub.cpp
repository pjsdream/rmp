#include <rmp/comm/subscriber.h>

#include <thread>
#include <iostream>

int main()
{
  std::cout << "Testing subscriber\n";

  rmp::Subscriber subscriber("testing_topic", "127.0.0.1");

  while (true)
  {
    using namespace std::chrono_literals;

    bool first = true;
    while (!subscriber.eof())
    {
      double d;
      subscriber >> d;
      if (first || d == 99)
        std::cout << "[" << std::chrono::high_resolution_clock::now().time_since_epoch().count() << "] received " << d << "\n";
      first = false;
    }

    std::this_thread::sleep_for(16ms);
  }

  return 0;
}

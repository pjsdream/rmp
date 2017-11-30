#ifndef RMP_TIMER_H
#define RMP_TIMER_H

#include <chrono>
#include <thread>

namespace rmp
{
class Timer
{
public:
  Timer() = delete;

  explicit Timer(double time)
      : start_time_(std::chrono::high_resolution_clock::now()), time_(time), already_over_(false)
  {
  }

  bool isOver()
  {
    if (already_over_)
      return true;

    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start_time_;
    if (diff.count() >= time_)
    {
      already_over_ = true;
      return true;
    }
    return false;
  }

  void sleepUntil()
  {
    if (!isOver())
    {
      std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start_time_;
      auto remaining = time_ - diff.count();
      if (remaining > 0)
        std::this_thread::sleep_for(std::chrono::duration<double>(remaining));
    }
  }

private:
  double time_;
  bool already_over_;
  std::chrono::high_resolution_clock::time_point start_time_;
};
}

#endif //RMP_TIMER_H

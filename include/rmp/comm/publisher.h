#ifndef RMP_PUBLISHER_H
#define RMP_PUBLISHER_H

#include <string>

#include "serializer.h"
#include "context.h"

namespace rmp
{
class Publisher
{
public:
  Publisher(std::string topic, std::string ip)
      : topic_(std::move(topic))
  {
    zmq_socket_ = Context::getInstance()->createPublisherSocket(std::move(ip));
    serializer_ << topic_;
  }

  template<typename T>
  Publisher& operator<<(T&& message)
  {
    serializer_ << std::forward<T>(message);
    return *this;
  }

  void flush()
  {
    {
      const auto& buffer = serializer_.getBuffer();
      printf("sending: ");
      for (int i=0; i<buffer.size(); i++)
        printf("%d ", buffer[i]);
      printf("\n");
      zmq_socket_->send(buffer.begin(), buffer.end());
    }

    serializer_.clear();
    serializer_ << topic_;
  }

private:
  std::string topic_;
  std::unique_ptr<zmq::socket_t> zmq_socket_;

  Serializer serializer_;
};
}

#endif //RMP_PUBLISHER_H

#ifndef RMP_REQUEST_H
#define RMP_REQUEST_H

namespace rmp
{
class Request
{
public:
  enum class Type : unsigned char
  {
    Clear = 0,
    Mesh,
    CustomMesh,
    CustomTexture,
    Frame,
    FrameAttach,
    Light,
  };

  Request() = delete;
  explicit Request(Type type)
      : type_(type)
  {
  }

  virtual ~Request() = default;

  Type type() const
  {
    return type_;
  }

private:
  Type type_;
};
}

#endif //RMP_REQUEST_H

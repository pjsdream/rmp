#ifndef RMP_REQUEST_MESH_H
#define RMP_REQUEST_MESH_H

#include <string>

#include "request.h"

namespace rmp
{
class RequestMesh : public Request
{
public:
  RequestMesh() : Request(Request::Type::Mesh)
  {
  }

  ~RequestMesh() override = default;

  std::string name;
  std::string filename;

  template<typename Archive>
  Archive& serialize(Archive& ar)
  {
    return ar & name & filename;
  }

private:
};
}

#endif //RMP_REQUEST_MESH_H

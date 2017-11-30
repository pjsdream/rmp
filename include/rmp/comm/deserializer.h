#ifndef RMP_DESERIALIZER_H
#define RMP_DESERIALIZER_H

#include <type_traits>

#include <Eigen/Dense>

namespace rmp
{
class Deserializer
{
public:
  Deserializer() = delete;
  explicit Deserializer(char* buffer)
      : buffer_(buffer)
  {
  }

  auto pointer() const
  {
    return buffer_;
  }

  Deserializer& operator<<(int size)
  {
    buffer_ -= size;
    return *this;
  }

  // Forward & operator with any type to corresponding << operators
  template<typename T>
  Deserializer& operator&(T&& t)
  {
    using type = typename std::remove_reference_t<T>;
    return *this >> std::forward<T>(t);
  }

  // For compound types, use the user-defined serialization functions
  template<typename T>
  Deserializer& deserialize(T& v, std::true_type)
  {
    v.serialize(*this);
    return *this;
  }

  template<typename T>
  Deserializer& deserialize(T& v, std::false_type)
  {
    // Operators for default data types
    constexpr auto size = sizeof(T);

    union FundamentalTypeDeconstructor
    {
      char c[size];
      T value;
    } u;

    for (int i = 0; i < size; i++)
      u.c[i] = *(char*) (buffer_++);
    v = u.value;

    return *this;
  };

  template<typename T>
  Deserializer& operator>>(T&& v)
  {
    using type = typename std::remove_reference_t<T>;
    return deserialize(v,
                       std::is_same<std::integral_constant<bool,
                       std::is_compound<type>::value && !std::is_enum<type>::value>,
                       std::true_type>());
  };

  // std::string argument
  Deserializer& operator>>(std::string& s)
  {
    decltype(s.length()) length;

    // As a result, index_ will increase by the number of bytes for string length
    *this >> length;

    s.resize(length);
    for (auto i = 0; i < length; i++)
      s[i] = *(char*) (buffer_++);

    return *this;
  }

  // std::vector argument
  template<typename T>
  Deserializer& operator>>(std::vector<T>& v)
  {
    decltype(v.size()) length;
    *this >> length;
    v.resize(length);

    for (int i = 0; i < length; i++)
      *this >> v[i];

    return *this;
  }

  // Eigen::Matrix argument
  template<typename base_type, int n, int m>
  Deserializer& operator>>(Eigen::Matrix<base_type, n, m>& v)
  {
    for (int i=0; i<n; i++)
      for (int j=0; j<m; j++)
        *this >> v(i, j);

    return *this;
  }

  // Eigen::Transform argument
  template<typename base_type, int n, int m>
  Deserializer& operator>>(Eigen::Transform<base_type, n, m>& v)
  {
    for (int i = 0; i < v.rows(); i++)
      for (int j = 0; j < v.cols(); j++)
        *this >> v.matrix()(i, j);

    return *this;
  }

private:
  char* buffer_;
};
}

#endif //RMP_DESERIALIZER_H

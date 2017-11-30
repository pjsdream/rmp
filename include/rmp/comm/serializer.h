#ifndef RMP_SERIALIZER_H
#define RMP_SERIALIZER_H

#include <Eigen/Dense>

namespace rmp
{
class Serializer
{
public:
  void clear()
  {
    buffer_.clear();
  }

  const std::vector<char>& getBuffer() const
  {
    return buffer_;
  }

  // Forward & operator with any type to corresponding << operators
  template<typename T>
  Serializer& operator&(T&& t)
  {
    using type = typename std::remove_reference_t<T>;
    return *this << std::forward<type>(t);
  }

  // For compound types, use the user-defined serialization functions
  template<typename T>
  Serializer& serialize(T&& v, std::true_type)
  {
    return v.serialize(*this);
  }

  // Operators for primitive data types
  template<typename T>
  Serializer& serialize(T&& v, std::false_type)
  {
    constexpr auto size = sizeof(T);

    union
    {
      char c[size];
      T value;
    } u{.value = v};
    buffer_.insert(buffer_.end(), u.c, u.c + size);
    return *this;
  }

  // Universal reference
  template<typename T>
  Serializer& operator<<(T&& v)
  {
    using type = typename std::remove_reference_t<T>;
    return serialize(std::forward<type>(v),
                     std::is_same<std::integral_constant<bool,
                     std::is_compound<type>::value && !std::is_enum<type>::value>,
                     std::true_type>());
  }

  // std::string argument
  Serializer& operator<<(std::string& s)
  {
    *this << s.length();
    buffer_.insert(buffer_.end(), std::begin(s), std::end(s));
    return *this;
  }

  Serializer& operator<<(std::string&& s)
  {
    *this << s.length();
    buffer_.insert(buffer_.end(), std::begin(s), std::end(s));
    return *this;
  }

  // std::vector argument
  template<typename T>
  Serializer& operator<<(std::vector<T>&& v)
  {
    *this << v.size();
    for (auto& element : v)
      *this << element;
    return *this;
  }

  template<typename T>
  Serializer& operator<<(std::vector<T>& v)
  {
    *this << v.size();
    for (auto& element : v)
      *this << element;
    return *this;
  }

  // Eigen::matrix argument
  template<typename base_type, int n, int m>
  Serializer& operator<<(Eigen::Matrix<base_type, n, m>&& v)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        *this << v(i, j);

    return *this;
  }

  template<typename base_type, int n, int m>
  Serializer& operator<<(Eigen::Matrix<base_type, n, m>& v)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        *this << v(i, j);

    return *this;
  }

  // Eigen::transform argument
  template<typename base_type, int n, int m>
  Serializer& operator<<(Eigen::Transform<base_type, n, m>&& v)
  {
    for (int i = 0; i < v.rows(); i++)
      for (int j = 0; j < v.cols(); j++)
        *this << v.matrix()(i, j);

    return *this;
  }

  template<typename base_type, int n, int m>
  Serializer& operator<<(Eigen::Transform<base_type, n, m>& v)
  {
    for (int i = 0; i < v.rows(); i++)
      for (int j = 0; j < v.cols(); j++)
        *this << v.matrix()(i, j);

    return *this;
  }

private:
  std::vector<char> buffer_;
};
}

#endif //RMP_SERIALIZER_H

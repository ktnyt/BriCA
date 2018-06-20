#ifndef __BRICA_KERNEL_BUFFER_HPP__
#define __BRICA_KERNEL_BUFFER_HPP__

#include <memory>

namespace brica {

class Buffer {
 public:
  using iterator = char*;
  using const_iterator = const char*;

  Buffer(std::size_t size) : ptr(std::make_shared<internal>(size)) {}
  Buffer(const Buffer& other) : ptr(other.ptr) {}
  Buffer(Buffer&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
  virtual ~Buffer() {}

  Buffer& operator=(const Buffer& other) {
    Buffer another(other);
    *this = std::move(another);
    return *this;
  }

  Buffer& operator=(Buffer&& other) {
    using std::swap;
    swap(*this, other);
    return *this;
  }

  iterator begin() noexcept { return ptr->buffer; }
  const_iterator begin() const noexcept { return ptr->buffer; }
  iterator end() noexcept { return ptr->buffer + ptr->size; }
  const_iterator end() const noexcept { return ptr->buffer + ptr->size; }
  const_iterator cbegin() const noexcept { return ptr->buffer; }
  const_iterator cend() const noexcept { return ptr->buffer + ptr->size; }

  char* data() noexcept { return ptr->buffer; }
  const char* data() const noexcept { return ptr->buffer; }
  std::size_t size() const noexcept { return ptr->size; }

  friend bool operator==(Buffer& a, Buffer& b) { return a.ptr == b.ptr; }
  friend bool operator!=(Buffer& a, Buffer& b) { return a.ptr != b.ptr; }
  friend bool operator<=(Buffer& a, Buffer& b) { return a.ptr <= b.ptr; }
  friend bool operator<(Buffer& a, Buffer& b) { return a.ptr < b.ptr; }
  friend bool operator>=(Buffer& a, Buffer& b) { return a.ptr >= b.ptr; }
  friend bool operator>(Buffer& a, Buffer& b) { return a.ptr > b.ptr; }

  friend void swap(Buffer& a, Buffer& b) {
    using std::swap;
    swap(a.ptr, b.ptr);
  }

 private:
  struct internal {
    internal(std::size_t size) : size(size), buffer(new char[size]) {}
    ~internal() { delete[] buffer; }

    std::size_t size;
    char* buffer;
  };
  std::shared_ptr<internal> ptr;
};

}  // namespace brica

#endif  // __BRICA_KERNEL_BUFFER_HPP__

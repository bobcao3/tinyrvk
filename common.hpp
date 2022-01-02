#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <limits>

namespace tinyrvk {

class BitMap {
 private:
  uint32_t *map;

 public:
  BitMap(size_t base_addr) {
    map = (uint32_t *)base_addr;
  }
  
  bool get(size_t index) {
    return ((map[index >> 5] >> (index & 31)) & 1) > 0;
  }

  void set(size_t index) {
    map[index >> 5] |= 1 << (index & 31);
  }

  void clear(size_t index) {
    map[index >> 5] &= ~(1 << (index & 31));
  }

  static size_t compute_size(size_t num_entries) {
    return (num_entries >> 5) + ((num_entries & 31) > 0 ? 1 : 0);
  }
};

template<typename T, size_t size>
class RingBuffer {
 private:
  T buffer[size];
  size_t write_idx{0};
  size_t read_idx{0};
  size_t usage{0};

 public:
  void push(T obj) {
    write_idx = (write_idx + 1) % size;
    usage++;
    buffer[write_idx] = (obj);
  }

  T pop() {
    read_idx = (read_idx + 1) % size;
    usage--;
    return (buffer[read_idx]);
  }

  bool empty() {
    return write_idx == read_idx;
  }

  bool full() {
    return usage >= size;
  }
};

constexpr size_t align_up_pot(size_t v, size_t bits) {
  return ((v >> bits) + (v & ((1 << bits) - 1)) ? 1 : 0) << bits;
}

}
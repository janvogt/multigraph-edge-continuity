// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.de>

#ifndef MODELS_MEMORYPAGE_HPP_
#define MODELS_MEMORYPAGE_HPP_

#include <vector>

enum class ByteOrder {
    LittleEndian, BigEndian
};

// Class representing an arbitraty length memory buffer
class MemoryPage {
 public:
  MemoryPage()=default;
  MemoryPage(const unsigned char * buffer, size_t length);

  // Read the next byte.
  unsigned char readByte() const;

  // Read the next int interpreting bytes with given order.
  uint32_t readInt(ByteOrder order) const;

  // Read the next double interpreting bytes with given order.
  double readDouble(ByteOrder order) const;

 private:
    std::vector<unsigned char> buf_;
    mutable size_t pos_ = 0;
};

#endif  // MODELS_MEMORYPAGE_HPP_

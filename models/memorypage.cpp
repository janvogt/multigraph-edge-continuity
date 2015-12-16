#include "memorypage.hpp"

// _____________________________________________________________________________
MemoryPage::MemoryPage(const uint8_t * buffer, size_t length) {
  for (size_t i = 0; i < length; i++) {
    buf_.push_back(buffer[i]);
  }
}

// _____________________________________________________________________________
uint8_t MemoryPage::readByte() const {
  return buf_.at(pos_++);
}

// _____________________________________________________________________________
uint32_t MemoryPage::readInt(ByteOrder order) const {
  size_t size = sizeof(uint32_t);
  uint32_t retVal = 0;
  for (uint8_t i = 0; i < size; i++) {
    uint32_t byte = readByte();
    retVal |= byte << (order == ByteOrder::BigEndian ? size - 1 - i : i) * 8;
  }
  return retVal;
}

// _____________________________________________________________________________
double MemoryPage::readDouble(ByteOrder order) const {
  size_t size = sizeof(uint64_t);
  uint64_t retVal = 0;
  for (uint8_t i = 0; i < size; i++) {
    uint64_t byte = readByte();
    retVal |= byte << (order == ByteOrder::BigEndian ? size - 1 - i : i) * 8;
  }
  return *(reinterpret_cast<double *>(&retVal));
}
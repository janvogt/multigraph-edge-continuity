#include "gtest/gtest.h"

#include "ewkb.hpp"
#include <iostream>
#include <string>

TEST(EWKBTest, TestUintExtraction) {
  std::istringstream is("\x01\x02\x03\x04", std::ios_base::binary);
  EWKB::EndianAware<uint32_t> integer;
  integer.bo = EWKB::ByteOrder::BigEndian;
  is >> integer;
  ASSERT_EQ(0x01020304, integer.value);
  is.seekg(0);
  integer.bo = EWKB::ByteOrder::LittleEndian;
  is >> integer;
  ASSERT_EQ(0x04030201, integer.value);
}

TEST(EWKBTest, TestDoubleExtraction) {
  //  +1 *   2^8  *  1 + 1/2 + 1/16 + 1/128 + 1/256 + 1/1024 = 1613/4 = 403.25
  // |0|100 0000 0111 |1001 0011 0100 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000|
  std::string buf {
      0x40, 0x79, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, // BigEndian
      0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x79, 0x40  // LittleEndian
  };
  std::istringstream is(buf, std::ios_base::binary);
  EWKB::EndianAware<double> real;
  real.bo = EWKB::ByteOrder::BigEndian;
  is >> real;
  ASSERT_EQ(403.25, real.value);
  real.bo = EWKB::ByteOrder::LittleEndian;
  is >> real;
  ASSERT_EQ(403.25, real.value);
}



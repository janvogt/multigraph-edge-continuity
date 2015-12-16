#include <gtest/gtest.h>
#include "memorypage.hpp"

TEST(MemoryPageTest, TestConstruction) {
    unsigned char testBuf[] {0x01, 0x02};
    MemoryPage b(testBuf, 2);
    ASSERT_TRUE(true);
}

TEST(MemoryPageTest, TestReadByte) {
    unsigned char testBuf[] {0x01, 0x02};
    MemoryPage b(testBuf, 2);
    ASSERT_EQ(1, b.readByte());
}

TEST(MemoryPageTest, TestReadInt) {
    unsigned char testBuf[] {0x01, 0x02, 0x03, 0x04};
    MemoryPage b(testBuf, 4);
    ASSERT_EQ(0x01020304, b.readInt(ByteOrder::BigEndian));
    MemoryPage b2(testBuf, 4);
    ASSERT_EQ(0x04030201, b2.readInt(ByteOrder::LittleEndian));
}

TEST(MemoryPageTest, TestReadDouble) {
    //  +1 *   2^8  *  1 + 1/2 + 1/16 + 1/128 + 1/256 + 1/1024 = 1613/4 = 403.25
    // |0|100 0000 0111 |1001 0011 0100 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000|
    unsigned char bigEndBuf[] {0x40, 0x79, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char littleEndBuf[] {0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x79, 0x40};
    MemoryPage b(bigEndBuf, 8);
    ASSERT_EQ(403.25, b.readDouble(ByteOrder::BigEndian));
    MemoryPage b2(littleEndBuf, 8);
    ASSERT_EQ(403.25, b2.readDouble(ByteOrder::LittleEndian));
}

TEST(MemoryPageTest, TestReadMultipleValues) {
    unsigned char bigEndBuf[] {0x0F, 0x01, 0x02, 0x03, 0x04, 0x40, 0x79, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00};
    MemoryPage b(bigEndBuf, 13);
    ASSERT_EQ(15, b.readByte());
    ASSERT_EQ(0x01020304, b.readInt(ByteOrder::BigEndian));
    ASSERT_EQ(403.25, b.readDouble(ByteOrder::BigEndian));
    unsigned char littleEndBuf[] {0x0F, 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x79, 0x40};
    MemoryPage b2(littleEndBuf, 13);
    ASSERT_EQ(15, b2.readByte());
    ASSERT_EQ(0x04030201, b2.readInt(ByteOrder::LittleEndian));
    ASSERT_EQ(403.25, b2.readDouble(ByteOrder::LittleEndian));
}
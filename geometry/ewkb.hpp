// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.com>

#ifndef GEOMETRY_EWKB_HPP_
#define GEOMETRY_EWKB_HPP_

#include <iostream>
#include <algorithm>
#include <cstdlib>

namespace EWKB {
  enum class ByteOrder : uint8_t {
    BigEndian = 0,
    LittleEndian = 1
  };

  inline ByteOrder systemByteOrder() {
    const uint16_t test = 0xFF00;
    return *reinterpret_cast<const uint8_t *>(&test) == 0xFF ?
        ByteOrder::BigEndian :
        ByteOrder::LittleEndian;
  }

  // Source https://github.com/postgis/postgis/blob/2.1.0/doc/ZMSgeoms.txt
  enum class GeometryType : uint32_t {
    wkbPoint = 1,
    wkbLineString = 2,
    wkbPolygon = 3,
    wkbMultiPoint = 4,
    wkbMultiLineString = 5,
    wkbMultiPolygon = 6,
    wkbGeometryCollection = 7,

    // | 0x80000000
    wkbPointZ = 0x80000001,
    wkbLineStringZ = 0x80000002,
    wkbPolygonZ = 0x80000003,
    wkbMultiPointZ = 0x80000004,
    wkbMultiLineStringZ = 0x80000005,
    wkbMultiPolygonZ = 0x80000006,
    wkbGeometryCollectionZ = 0x80000007,

    // | 0x40000000
    wkbPointM = 0x40000001,
    wkbLineStringM = 0x40000002,
    wkbPolygonM = 0x40000003,
    wkbMultiPointM = 0x40000004,
    wkbMultiLineStringM = 0x40000005,
    wkbMultiPolygonM = 0x40000006,
    wkbGeometryCollectionM = 0x40000007,

    // | 0x40000000 | 0x80000000
    wkbPointZM = 0xC0000001,
    wkbLineStringZM = 0xC0000002,
    wkbPolygonZM = 0xC0000003,
    wkbMultiPointZM = 0xC0000004,
    wkbMultiLineStringZM = 0xC0000005,
    wkbMultiPolygonZM = 0xC0000006,
    wkbGeometryCollectionZM = 0xC0000007,

    // | 0x20000000
    wkbPointS = 0x20000001,
    wkbLineStringS = 0x20000002,
    wkbPolygonS = 0x20000003,
    wkbMultiPointS = 0x20000004,
    wkbMultiLineStringS = 0x20000005,
    wkbMultiPolygonS = 0x20000006,
    wkbGeometryCollectionS = 0x20000007,

    // | 0x20000000 | 0x80000000
    wkbPointZS = 0xA0000001,
    wkbLineStringZS = 0xA0000002,
    wkbPolygonZS = 0xA0000003,
    wkbMultiPointZS = 0xA0000004,
    wkbMultiLineStringZS = 0xA0000005,
    wkbMultiPolygonZS = 0xA0000006,
    wkbGeometryCollectionZS = 0xA0000007,

    // | 0x20000000 | 0x40000000
    wkbPointMS = 0x60000001,
    wkbLineStringMS = 0x60000002,
    wkbPolygonMS = 0x60000003,
    wkbMultiPointMS = 0x60000004,
    wkbMultiLineStringMS = 0x60000005,
    wkbMultiPolygonMS = 0x60000006,
    wkbGeometryCollectionMS = 0x60000007,

    // | 0x20000000 | 0x40000000 | 0x80000000
    wkbPointZMS = 0xE0000001,
    wkbLineStringZMS = 0xE0000002,
    wkbPolygonZMS = 0xE0000003,
    wkbMultiPointZMS = 0xE0000004,
    wkbMultiLineStringZMS = 0xE0000005,
    wkbMultiPolygonZMS = 0xE0000006,
    wkbGeometryCollectionZMS = 0xE0000007,
  };

  template <typename T>
  struct EndianAware {
    T value;
    ByteOrder bo;
  };

  template <typename T>
  std::ostream& operator<<(std::ostream& os, const EWKB::EndianAware<T>& obj) {
    std::size_t len = sizeof(T);
    T buf {obj.value};
    std::ostream::char_type * bytes = reinterpret_cast<std::ostream::char_type *>(&buf);
    if (obj.bo != EWKB::systemByteOrder()) {
      std::reverse(bytes, bytes + len);
    }
    return os.write(bytes, static_cast<std::streamsize>(len));
  }

  template <typename T>
  std::istream& operator>>(std::istream& is, EWKB::EndianAware<T>& obj) {
    std::size_t len = sizeof(T);
    std::istream::char_type * bytes = reinterpret_cast<std::istream::char_type *>(&obj.value);
    is.read(bytes, static_cast<std::streamsize>(len));
    if (obj.bo != EWKB::systemByteOrder()) {
      std::reverse(bytes, bytes + len);
    }
    return is;
  }
}

#endif  // GEOMETRY_EWKB_HPP_
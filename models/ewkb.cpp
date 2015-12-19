// #include "ewkb.hpp"

// EWKB::ByteOrder EWKB::systemByteOrder() {
//   const uint16_t test = 0xFF00;
//   return *reinterpret_cast<const uint8_t *>(&test) == 0xFF ?
//       EWKB::ByteOrder::BigEndian :
//       EWKB::ByteOrder::LittleEndian;
// }
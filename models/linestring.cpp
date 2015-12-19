#include "linestring.hpp"

#include <bitset>
#include <iostream>
#include <limits>

#include "ewkb.hpp"

// _____________________________________________________________________________
const std::vector<Point>& Geometry::LineString::vertices() {
  return vertices_;
}

// _____________________________________________________________________________
std::string Geometry::LineString::toString() {
  std::ostringstream os;
  os.precision(12);
  if (hasSrid_) {
    os << "SRID=" << srid_ <<  ';';
  }
  os << "LINESTRING(";
  for (Point p : vertices_) {
    os << p.x() << ' ' << p.y() << ',';
  }
  os.seekp(-1, std::ios_base::cur);
  os << ')';
  return os.str();
}


std::istream& Geometry::operator>>(std::istream& is, Geometry::LineString& obj) {
  uint8_t orderFlag;
  is.get(*reinterpret_cast<std::istream::char_type *>(&orderFlag));
  EWKB::ByteOrder bo = orderFlag ? EWKB::ByteOrder::LittleEndian : EWKB::ByteOrder::BigEndian;
  EWKB::EndianAware<uint32_t> type {0, bo};
  is >> type;
  EWKB::EndianAware<uint32_t> srid {0, bo};
  switch(type.value) {
    case static_cast<uint32_t>(EWKB::GeometryType::wkbLineStringS):
      is >> srid;
      obj.hasSrid_ = true;
      obj.srid_ = srid.value;
      // fallthrough.
    case static_cast<uint32_t>(EWKB::GeometryType::wkbLineString):
      break;
    default:
      is.setstate(std::ios::failbit);
      return is;
  }
  EWKB::EndianAware<uint32_t> length {0, bo};
  is >> length;
  EWKB::EndianAware<double> x {0, bo}, y {0, bo};
  for (uint32_t i = 0; i < length.value; i++) {
    is >> x >> y;
    obj.vertices_.push_back(Point(x.value, y.value));
  }
  if (!is) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::ostream& Geometry::operator<<(std::ostream& os, const Geometry::LineString& obj) {
  const auto bo = EWKB::systemByteOrder();
  os.put(static_cast<std::ostream::char_type>(bo));
  EWKB::EndianAware<uint32_t> integer{0, bo};
  integer.value = static_cast<uint32_t>(obj.hasSrid_ ? EWKB::GeometryType::wkbLineStringS : EWKB::GeometryType::wkbLineString);
  os << integer;
  if (obj.hasSrid_) {
    integer.value = obj.srid_;
    os << integer;
  }
  assert(obj.vertices_.size() < std::numeric_limits<uint32_t>::max());
  integer.value = static_cast<uint32_t>(obj.vertices_.size());
  os << integer;
  EWKB::EndianAware<double> x{0, bo}, y{0, bo};
  for (const auto p : obj.vertices_) {
    x.value = CGAL::to_double(p.x());
    y.value = CGAL::to_double(p.y());
    os << x << y;
  }
  return os;
}
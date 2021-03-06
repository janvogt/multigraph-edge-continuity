// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.com>

#ifndef GEOMETRY_LINESTRING_HPP_
#define GEOMETRY_LINESTRING_HPP_

#include <vector>
#include <iostream>

#include "cgaltypes.hpp"

namespace Geometry {
  class LineString {
   public:
    // Get the vertices of this LineString
    const std::vector<Point>& vertices() const;

    // As (rounded) EWKT String
    std::string toString() const;

   private:
    friend std::istream& operator>>(std::istream& is, LineString& obj);
    friend std::ostream& operator<<(std::ostream& os, const LineString& obj);
    std::vector<Point> vertices_;
    bool hasSrid_ = false;
    uint32_t srid_ = 0;
  };

  std::istream& operator>>(std::istream& is, Geometry::LineString& obj);
  std::ostream& operator<<(std::ostream& os, const Geometry::LineString& obj);
}

#endif  // GEOMETRY_LINESTRING_HPP_
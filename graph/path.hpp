// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.com>

#ifndef GRAPH_PATH_HPP_
#define GRAPH_PATH_HPP_

#include <string>

#include "../geometry/linestring.hpp"

namespace Graph {
  // A path.
  class Path {
   public:
    Path(std::string name, Geometry::LineString geom):name_(std::move(name)), geom_(std::move(geom)){};

    std::string toString() const;
   private:
    std::string name_;
    Geometry::LineString geom_;
    uint64_t split_order;
  };
}

#endif  // GRAPH_PATH_HPP_
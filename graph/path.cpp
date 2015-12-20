// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.com>

#include "path.hpp"
#include <iostream>

// _____________________________________________________________________________
std::string Graph::Path::toString() const {
  std::ostringstream os;
  os << "Path@" << this << "(name=" << name_ << ", geom=" << geom_.toString()
    << ')';
  return os.str();
}
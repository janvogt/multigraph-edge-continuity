// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.com>

#ifndef HELPER_HELPER_HPP_
#define HELPER_HELPER_HPP_

#include <iostream>

namespace Helper {
  struct StreamGuard {
    std::istream& stream;
    std::ios_base::iostate oldstate = stream.exceptions();
    StreamGuard(std::istream& s) : stream(s) {
      stream.exceptions(oldstate | std::istream::eofbit | std::istream::failbit | std::istream::badbit);
    }
    ~StreamGuard() {
      stream.exceptions(oldstate);
    }
  };
}

#endif  // HELPER_HELPER_HPP_
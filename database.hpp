// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.com>

#ifndef MULTIGRAPH_EDGE_CONTINUITY_DATABASE_HPP_
#define MULTIGRAPH_EDGE_CONTINUITY_DATABASE_HPP_

#include <string>
#include <vector>
#include <pqxx/pqxx>

#include "graph/path.hpp"
#include "graph/edge.hpp"

// Database connection for reading and writing results.
class DataBase {
 public:
  // Create a new instance using the given connection string.
  explicit DataBase(const std::string& dsn): con_(dsn){};

  // Read paths stored in db.
  std::vector<Graph::Path> readPaths();

  // Write edges back to db.
  //void writeEdges(const &std::vector<Graph::Edge>);

 private:
    pqxx::connection con_;
};

#endif  // MULTIGRAPH_EDGE_CONTINUITY_DATABASE_HPP_
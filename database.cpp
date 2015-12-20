// Copyright 2015, Jan Vogt.
// Author: Jan Vogt <jan.vogt@me.com>

#include "database.hpp"

#include <iostream>

#include "helper/helper.hpp"

// _____________________________________________________________________________
std::vector<Graph::Path> DataBase::readPaths() {
    pqxx::work w(con_);
    auto result = w.exec("SELECT ST_AsEWKB(geom) geom, path FROM test_network");
    std::vector<Graph::Path> paths;
    for (auto const& row : result) {
        std::istringstream is(pqxx::binarystring(row["geom"]).str(), std::ios_base::binary);
        Helper::StreamGuard guard(is);
        Geometry::LineString geom;
        is >> geom;
        paths.push_back(Graph::Path(pqxx::to_string(row["path"]), geom));
    }
    return paths;
}
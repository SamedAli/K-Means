#pragma once

#include <vector>

#include "point.h"

namespace csvHandler
{
    std::vector<point::Point2D> readcsv();
    void write_to_file(const std::vector<point::Point2D> *points);
}

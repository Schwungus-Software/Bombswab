#pragma once

#include <vector>

struct Point {
    int x, y;
};

std::vector<Point> rasterize(Point, Point);
std::vector<Point> rasterize(int, int, int, int);

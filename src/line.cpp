#include <algorithm>
#include <cmath>

#include "line.hpp"

std::vector<Point> rasterize(int x0, int y0, int x1, int y1) {
  return rasterize({x0, y0}, {x1, y1});
}

std::vector<Point> rasterize(Point start, Point end) {
  std::vector<Point> result;

  const auto dx = std::abs(end.x - start.x);
  const auto dy = std::abs(end.y - start.y);

  const auto x_dir = dx == 0 ? 0 : (end.x - start.x) / dx;
  const auto y_dir = dy == 0 ? 0 : (end.y - start.y) / dy;

  auto x = start.x, y = start.y;
  result.push_back(start);

  if (dy <= dx) {
    auto steps = dx;
    auto d = dy - (dx / 2);

    while (steps-- > 0) {
      x += x_dir;

      if (d < 0) {
        d += dy;
      } else {
        d += dy - dx;
        result.push_back({x, y});

        y += y_dir;
      }

      result.push_back({x, y});
    }
  } else {
    auto steps = dy;
    auto d = dx - (dy / 2);

    while (steps-- > 0) {
      y += y_dir;

      if (d < 0) {
        d += dx;
      } else {
        d += dx - dy;
        result.push_back({x, y});

        x += x_dir;
      }

      result.push_back({x, y});
    }
  }

  return result;
}

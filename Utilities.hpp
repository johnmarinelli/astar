#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cmath>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int CELL_HEIGHT = 96;
const int CELL_WIDTH = 92;

inline int getManhattanDistance(int x1, int y1, int x2, int y2)
{
	return std::abs(x2-x1) + std::abs(y2-y1);
}

#endif

#include "header.h"
#include <cmath>
namespace Math
{
float GetDistance(float x1, float y1, float x2, float y2)
{
	return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
}

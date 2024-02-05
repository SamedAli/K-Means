#include "../includes/point.h"

#include <limits>

namespace point{
    Point2D::Point2D() : m_x{ 0.0 }, m_y{ 0.0 }, m_cluster{ -1 }, m_min_distance{ std::numeric_limits<double>::max() } {}
    Point2D::Point2D(double x, double y) : m_x{x}, m_y{y}, m_cluster{ -1 }, m_min_distance{ std::numeric_limits<double>::max() } {}

    double Point2D::distance(Point2D p)
	{
		return (p.m_x - m_x) * (p.m_x - m_x) + (p.m_y - m_y) * (p.m_y - m_y);
	}
}
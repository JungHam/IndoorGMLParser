#include "LinearRing2D.h"
#include "logger.h"
#include <float.h>
#include <assert.h>


namespace geometry {

	
	LinearRing2D::LinearRing2D() {

	}

	bool LinearRing2D::isExterior() const
	{
		return m_exterior;
	}

	unsigned int LinearRing2D::size() const
	{
		return m_vertices.size();
	}

	void LinearRing2D::addVertex(const Point2D& v)
	{
		m_vertices.push_back(v);
	}

	/*
	Point2D LinearRing2D::computeNormal() const
	{
	unsigned int len = size();
	if (len < 3) return Point2D();

	// Tampieri, F. 1992. Newell's method for computing the plane equation of a polygon. In Graphics Gems III, pp.231-232.
	Point2D n(0., 0., 0.);
	for (unsigned int i = 0; i < len; i++)
	{
	const Point2D& current = m_vertices[i];
	const Point2D& next = m_vertices[(i + 1) % len];

	n.x += (current.y - next.y) * (current.z + next.z);
	n.y += (current.z - next.z) * (current.x + next.x);
	n.z += (current.x - next.x) * (current.y + next.y);
	}
	return n.normal();
	}
	*/

	std::vector<Point2D>& LinearRing2D::getVertices()
	{
		return m_vertices;
	}

	void LinearRing2D::setVertices(std::vector<Point2D> vertices)
	{
		m_vertices = vertices;
	}

	const std::vector<Point2D>& LinearRing2D::getVertices() const
	{
		return m_vertices;
	}

	void LinearRing2D::forgetVertices()
	{
		m_vertices.clear();
	}

}

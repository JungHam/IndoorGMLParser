#include "linearring.h"
#include "logger.h"
#include <float.h>
#include <assert.h>


namespace indoorgml {

	LinearRing::LinearRing(const std::string& id, bool isExterior) : AbstractFeatures(id), m_exterior(isExterior)
	{

	}
	LinearRing::LinearRing(const std::string& id): AbstractFeatures(id) {
		
	}

	bool LinearRing::isExterior() const
	{
		return m_exterior;
	}

	unsigned int LinearRing::size() const
	{
		return m_vertices.size();
	}

	void LinearRing::addVertex(const TVec3d& v)
	{
		m_vertices.push_back(v);
	}

	/*
	TVec3d LinearRing::computeNormal() const
	{
		unsigned int len = size();
		if (len < 3) return TVec3d();

		// Tampieri, F. 1992. Newell's method for computing the plane equation of a polygon. In Graphics Gems III, pp.231-232.
		TVec3d n(0., 0., 0.);
		for (unsigned int i = 0; i < len; i++)
		{
			const TVec3d& current = m_vertices[i];
			const TVec3d& next = m_vertices[(i + 1) % len];

			n.x += (current.y - next.y) * (current.z + next.z);
			n.y += (current.z - next.z) * (current.x + next.x);
			n.z += (current.x - next.x) * (current.y + next.y);
		}
		return n.normal();
	}
	*/

	std::vector<TVec3d>& LinearRing::getVertices()
	{
		return m_vertices;
	}

	void LinearRing::setVertices(std::vector<TVec3d> vertices)
	{
		m_vertices = vertices;
	}

	const std::vector<TVec3d>& LinearRing::getVertices() const
	{
		return m_vertices;
	}

	void LinearRing::forgetVertices()
	{
		m_vertices.clear();
	}

}

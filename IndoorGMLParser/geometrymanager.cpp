#include "geometrymanager.h"
#include "solid.h"
#include "polygon.h"


namespace indoorgml {

	GeometryManager::GeometryManager(const std::string& id) : AbstractFeatures(id)
	{

	}


	unsigned int GeometryManager::getPolygonsCount() const
	{
		return m_polygons.size();
	}

	std::shared_ptr<Polygon> GeometryManager::getPolygon(unsigned int i)
	{
		return m_polygons.at(i);
	}

	std::shared_ptr<const Polygon> GeometryManager::getPolygon(unsigned int i) const
	{
		return m_polygons.at(i);
	}

	unsigned int GeometryManager::getLineStringCount() const
	{
		return m_lineStrings.size();
	}

	std::shared_ptr<LineString> GeometryManager::getLineString(unsigned int i)
	{
		return m_lineStrings.at(i);
	}

	std::shared_ptr<const LineString> GeometryManager::getLineString(unsigned int i) const
	{
		return m_lineStrings.at(i);
	}

	unsigned int GeometryManager::getGeometriesCount() const
	{
		return m_childGeometries.size();
	}

	/*
	const GeometryManager& GeometryManager::getGeometry(unsigned int i) const
	{
		return *m_childGeometries.at(i);
	}

	GeometryManager& GeometryManager::getGeometry(unsigned int i)
	{
		return *m_childGeometries.at(i);
	}
	*/

	void GeometryManager::addGeometry(string type, AbstractFeatures geom)
	{
		
		if (type == "Solid") {
			
		}
		else if (type == "Surface") {}
		else if (type == "Polygon") {}
		else if (type == "LinearRing") {}
		else if (type == "LineString") {}
		else if (type == "Point") {}
		//m_childGeometries.push_back(std::unique_ptr<>(geom));
	}

	
	GeometryManager::~GeometryManager()
	{
	}

	void GeometryManager::addPolygon(std::shared_ptr<Polygon> p)
	{
		m_polygons.push_back(p);
	}

	void GeometryManager::addLineString(std::shared_ptr<LineString> l)
	{
		m_lineStrings.push_back(l);
	}

	void GeometryManager::finish(bool optimize, std::shared_ptr<Logger> logger)
	{
		// only need to finish geometry once
		if (m_finished) {
			return;
		}

		m_finished = true;

		//for (std::shared_ptr<GeometryManager>& child : m_childGeometries) {
		//	child->finish(optimize, logger);
		//}

		for (std::shared_ptr<Polygon>& polygon : m_polygons) {
			polygon->finish(optimize, logger);
		}

	}

	std::ostream& operator<<(std::ostream& os, const indoorgml::GeometryManager& s)
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < s.getPolygonsCount(); i++)
		{
			os << s.getPolygon(i);
			count += s.getPolygon(i)->getVertices().size();
		}

		os << "  @ " << s.getPolygonsCount() << " polys [" << count << " vertices]" << std::endl;

		return os;
	}

}

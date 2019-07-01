#ifndef _INDOORGMLFACTORY_H_
#define _INDOORGMLFACTORY_H_
#pragma once
#include <memory>
#include "geometrymanager.h"

namespace indoorgml {

	class AppearanceManager;
	class PolygonManager;
	class GeometryManager;
	class Logger;

	class Geometry;
	class Solid;
	class Polygon;
	class LineString;

	class IndoorGMLFactory {
		friend class GeometryFactory;
	public:
		IndoorGMLFactory::IndoorGMLFactory();

		std::shared_ptr<Solid> createSolid(const std::string& id);		
		std::shared_ptr<Polygon> createPolygon(const std::string& id);
		std::shared_ptr<LineString> createLineString(const std::string& id);
		std::unique_ptr<GeometryManager> getGeometryManager();
		void closeFactory();		
		~IndoorGMLFactory();
	protected:

		std::shared_ptr<Logger> m_logger;
		std::unique_ptr<GeometryManager> m_geometryManager;
		
	};

}
#endif


#pragma once

#include "geometrymanager.h"


#include <memory>

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
	public:
		IndoorGMLFactory(std::shared_ptr<Logger> logger);

		std::shared_ptr<Solid> createSolid(const std::string& id);		
		std::shared_ptr<Polygon> createPolygon(const std::string& id);
		std::shared_ptr<LineString> createLineString(const std::string& id);

		void closeFactory();

		~IndoorGMLFactory();
	protected:

		std::shared_ptr<Logger> m_logger;
		std::unique_ptr<GeometryManager> m_geometryManager;
	};

}


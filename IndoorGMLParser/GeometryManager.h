#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include "logger.h"
#include "geometrymanager.h"
#include "AbstractFeatures.h"
class Tesselator;

namespace indoorgml {

	class LineString;
	class Polygon;
	class IndoorGMLFactory;
	class IndoorGMLLogger;
	class Solid;

	class GeometryManager
	{
		friend class IndoorGMLFactory;
	public:
		

		unsigned int getSolidsCount() const;
		std::shared_ptr<Solid> getSolid(unsigned int i);
		std::shared_ptr<const Solid> getSolid(unsigned int i) const;
		std::shared_ptr<Solid> getSolid(string id);

		unsigned int getPolygonsCount() const;
		std::shared_ptr<Polygon> getPolygon(unsigned int i);
		std::shared_ptr<const Polygon> getPolygon(unsigned int i) const;

		unsigned int getLineStringCount() const;
		std::shared_ptr<LineString> getLineString(unsigned int i);
		std::shared_ptr<const LineString> getLineString(unsigned int i) const;

		unsigned int getGeometriesCount() const;
		const AbstractFeatures& getGeometry(unsigned int i) const;
		AbstractFeatures& getGeometry(unsigned int i);
		void addGeometry(string type, AbstractFeatures geom);

		void addPolygon(std::shared_ptr<Polygon>);
		void addLineString(std::shared_ptr<LineString>);
		void addSolid(std::shared_ptr<Solid>);

		/**
		* @brief finishes the geometry by finishing its child polygons after broadcasting its appearances to all child polygons
		* @param tesselate determines wether the polygons are tesselated
		* @param tesselator the tesselator to be used for tesselation
		* @param mergePolygons determines wether all polygons are merged into one
		*/
		void finish(bool optimize, std::shared_ptr<Logger> logger);

		~GeometryManager();


	protected:
		GeometryManager();

		bool m_finished;


		std::vector<std::shared_ptr<Solid> > m_childGeometries;
		std::vector<std::shared_ptr<Solid> > m_solids;
		std::vector<std::shared_ptr<Polygon> > m_polygons;
		std::vector<std::shared_ptr<LineString> > m_lineStrings;
	};

}

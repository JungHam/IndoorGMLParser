#include "indoorgmlfactory.h"
#include <iostream>
#include "solid.h"
#include "polygon.h"

using namespace std;

namespace indoorgml {

		IndoorGMLFactory::IndoorGMLFactory() {
			m_geometryManager = unique_ptr<GeometryManager>(new GeometryManager());
		}

		std::shared_ptr<Solid> IndoorGMLFactory::createSolid(const std::string& id) {
			shared_ptr<Solid> newFeature = shared_ptr<Solid>(new Solid(id));
			m_geometryManager->addSolid(newFeature);
			return newFeature;
		}
		std::shared_ptr<Polygon> IndoorGMLFactory::createPolygon(const std::string& id){
			shared_ptr<Polygon> newFeature = shared_ptr<Polygon>(new Polygon(id));
			m_geometryManager->addPolygon(newFeature);
			return newFeature;
		}
		//std::shared_ptr<LineString> IndoorGMLFactory::createLineString(const std::string& id) {}

}

#ifndef _POLYGON_H_
#define _POLYGON_H_
#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "linearring.h"
#include "geometrymanager.h"
#include "logger.h"
#include "Point3D.h"
#include "Face.h"
#include "Vertex.h"

using namespace geometry;
namespace indoorgml {

	class Polygon : public indoorgml::AbstractFeatures
	{
	
	public:

		// Get the vertices
		const std::vector<indoorgml::Point3D>& getVertices() const;
		std::vector<indoorgml::Point3D>& getVertices();

		// Get the indices
		const std::vector<unsigned int>& getIndices() const;

		bool negNormal() const;
		void setNegNormal(bool negNormal);

		void addRing(indoorgml::LinearRing*);

		geometry::Face convertFromPolygonToFace();
		void setExterior(shared_ptr<indoorgml::LinearRing> l);
		shared_ptr<indoorgml::LinearRing> getExterior();
		Polygon(string id);

		virtual ~Polygon();

	protected:
		//Polygon(const std::string& id);

		
		std::vector<indoorgml::Point3D> m_vertices;
		std::vector<unsigned int> m_indices;

		std::shared_ptr<indoorgml::LinearRing> m_exteriorRing;
		std::vector<std::shared_ptr<indoorgml::LinearRing> > m_interiorRings;

		bool m_negNormal;
		bool m_finished;

		//std::shared_ptr<Logger> m_logger;
	};
}
#endif
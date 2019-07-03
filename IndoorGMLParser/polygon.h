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

class Tesselator;

namespace indoorgml {



	/**
	* @brief The Polygon class implements the functionality of gml::Polygon and gml::SurfacePatch (gml::Rectangle, gml::Triangle) objects
	*/
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

		//void finish(bool optimize, std::shared_ptr<Logger> logger);

		std::shared_ptr<indoorgml::LinearRing> exteriorRing() {
			return m_exteriorRing;
		}

		const std::shared_ptr<indoorgml::LinearRing> exteriorRing() const {
			return m_exteriorRing;
		}

		std::vector<std::shared_ptr<indoorgml::LinearRing> >& interiorRings() {
			return m_interiorRings;
		}

		const std::vector<std::shared_ptr<indoorgml::LinearRing> >& interiorRings() const {
			return m_interiorRings;
		}
		void Polygon::setExterior(shared_ptr<indoorgml::LinearRing> l);
		shared_ptr<indoorgml::LinearRing> Polygon::getExterior();
		Polygon(string id);

		virtual ~Polygon();

	protected:
		//Polygon(const std::string& id);


		/**
		* @brief fill the vertex array and creates a corresponding index array
		* @param tesselate if true the tesselator will be used to tesselate the linear rings
		* @param tesselator the Tesselator object
		*/
		//void computeIndices(Tesselator& tesselator, std::shared_ptr<Logger> logger);

		
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
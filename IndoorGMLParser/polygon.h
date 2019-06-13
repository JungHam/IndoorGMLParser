#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "point.hpp"
#include "linearring.h"
#include "geometrymanager.h"
#include "logger.h"

class Tesselator;

namespace indoorgml{

	class CityGMLFactory;
	
	/**
	* @brief The Polygon class implements the functionality of gml::Polygon and gml::SurfacePatch (gml::Rectangle, gml::Triangle) objects
	*/
	class Polygon : public AbstractFeatures
	{
		friend class CityGMLFactory;
	public:
		
		// Get the vertices
		const std::vector<TVec3d>& getVertices() const;
		std::vector<TVec3d>& getVertices();

		// Get the indices
		const std::vector<unsigned int>& getIndices() const;

		bool negNormal() const;
		void setNegNormal(bool negNormal);

		void addRing(LinearRing*);

		void finish( bool optimize, std::shared_ptr<Logger> logger);

		std::shared_ptr<LinearRing> exteriorRing() {
			return m_exteriorRing;
		}

		const std::shared_ptr<LinearRing> exteriorRing() const {
			return m_exteriorRing;
		}

		std::vector<std::shared_ptr<LinearRing> >& interiorRings() {
			return m_interiorRings;
		}

		const std::vector<std::shared_ptr<LinearRing> >& interiorRings() const {
			return m_interiorRings;
		}

		virtual ~Polygon();

	protected:
		Polygon(const std::string& id, std::shared_ptr<Logger> logger);


		/**
		* @brief fill the vertex array and creates a corresponding index array
		* @param tesselate if true the tesselator will be used to tesselate the linear rings
		* @param tesselator the Tesselator object
		*/
		void computeIndices(Tesselator& tesselator, std::shared_ptr<Logger> logger);

		TVec3d computeNormal();

		std::vector<TVec3d> m_vertices;
		std::vector<unsigned int> m_indices;

		std::shared_ptr<LinearRing> m_exteriorRing;
		std::vector<std::shared_ptr<LinearRing> > m_interiorRings;

		bool m_negNormal;
		bool m_finished;

		std::shared_ptr<Logger> m_logger;
	};
}

#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_
#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "LinearRing2D.h"
#include "geometrymanager.h"
#include "logger.h"
#include "point2d.h"
#include "Triangle.h"

class Tesselator;

namespace geometry {



	/**
	* @brief The Polygon class implements the functionality of gml::Polygon and gml::SurfacePatch (gml::Rectangle, gml::Triangle) objects
	*/
	class Polygon2D 
	{
		friend class IndoorGMLFactory;
	public:
		// Get the vertices
		const std::vector<Point2D>& getVertices() const;
		std::vector<Point2D>& getVertices();

		// Get the indices
		const std::vector<unsigned int>& getIndices() const;

		bool negNormal() const;
		void setNegNormal(bool negNormal);

		void addRing(LinearRing2D*);

		//void finish(bool optimize, std::shared_ptr<Logger> logger);

		std::shared_ptr<LinearRing2D> exteriorRing();
		

		const std::shared_ptr<LinearRing2D> exteriorRing() const;

		std::vector<std::shared_ptr<LinearRing2D> >& interiorRings();

		const std::vector<std::shared_ptr<LinearRing2D> >& interiorRings() const;
		void Polygon2D::setExterior(shared_ptr<LinearRing2D> l);
		shared_ptr<LinearRing2D> Polygon2D::getExterior();
		Polygon2D(string id);
		Polygon2D();

		vector<int> calculateNormal();
		Point2D getEdgeVector(int index);
		Point2D getEdgeDirection(int index);
		vector<Polygon2D> tessellate(vector<int>list);
		virtual ~Polygon2D();
		vector<Point2D>getIndexToInsertBySquaredDist();
	protected:
		//Polygon(const std::string& id);


		/**
		* @brief fill the vertex array and creates a corresponding index array
		* @param tesselate if true the tesselator will be used to tesselate the linear rings
		* @param tesselator the Tesselator object
		*/
		//void computeIndices(Tesselator& tesselator, std::shared_ptr<Logger> logger);


		std::vector<Point2D> m_vertices;
		std::vector<unsigned int> m_indices;
		double _normal;
		std::shared_ptr<LinearRing2D> m_exteriorRing;
		std::vector<std::shared_ptr<LinearRing2D> > m_interiorRings;

		bool m_negNormal;
		bool m_finished;

		//std::shared_ptr<Logger> m_logger;
	};
}
#endif
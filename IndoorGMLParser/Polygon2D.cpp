#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "LinearRing2D.h"
#include "geometrymanager.h"
#include "logger.h"
#include "point2d.h"
#include "Polygon2D.h"


class Tesselator;

namespace geometry {



	// Get the vertices
	const std::vector<Point2D>& Polygon2D::getVertices() const {
		return m_vertices;
	}
	std::vector<Point2D>& Polygon2D::getVertices() {
		return m_vertices;
	}

	// Get the indices
	const std::vector<unsigned int>& Polygon2D::getIndices() const {
		return m_indices;
	}

	//bool Polygon2D::neg_normal() const {}
	//void Polygon2D::setNeg_normal(bool neg_normal) {}

	void Polygon2D::addRing(LinearRing2D*) {}

	//void finish(bool optimize, std::shared_ptr<Logger> logger);

	std::shared_ptr<LinearRing2D> Polygon2D::exteriorRing() {
		return m_exteriorRing;
	}

	const std::shared_ptr<LinearRing2D> Polygon2D::exteriorRing() const {
		return m_exteriorRing;
	}

	std::vector<std::shared_ptr<LinearRing2D> >& Polygon2D::interiorRings() {
		return m_interiorRings;
	}

	const std::vector<std::shared_ptr<LinearRing2D> >& Polygon2D::interiorRings() const {
		return m_interiorRings;
	}
	void Polygon2D::setExterior(shared_ptr<LinearRing2D> l) {
		m_exteriorRing = l;
	}
	shared_ptr<LinearRing2D> Polygon2D::getExterior() {
		return m_exteriorRing;
	}

	Point2D Polygon2D::getEdgeDirection(int index) {
		Point2D result = getEdgeVector(index);
		result.unitary();
		return result;
	}
	
	Point2D Polygon2D::getEdgeVector(int index) {
		//segment를 구하고
		Point2D curr = m_vertices.at(index);
		int vertexSize = m_vertices.size();
		int nextIndex = (index + 1)%vertexSize;
		Point2D next = m_vertices.at(nextIndex);
		
		//그 segment에서 getVector를 한다.
		Point2D result(curr.x - next.x, curr.y - next.y);

		return result;

	}

	vector<int> Polygon2D::calculateNormal() {
		vector<int> result;
		for (int i = 0; i < m_vertices.size(); i++) {
			Point2D temp = m_vertices.at(i);
			int prevIndex,nextIndex;
			if (i == 0) {
				prevIndex = m_vertices.size() - 1;
			}
			else {
				prevIndex = i - 1;
			}
			if (i == m_vertices.size() - 1) {
				nextIndex = 0;
			}
			else {
				nextIndex = i + 1;
			}
			Point2D start = getEdgeDirection(prevIndex);
			Point2D end = getEdgeDirection(i);
			
			double crossProd = start.cross(end);
			double scalaProd = start.scalar(end);

			if (crossProd < 0.0) {
				crossProd = -1;
				result.push_back(i);
			}
			else if (crossProd > 0.0) {
				crossProd = 1;
			}
			else {
				continue;
			}
			double cosAlfa = scalaProd;
			double alfa = acos(cosAlfa);
			_normal += crossProd * alfa;
		}

		if (_normal > 0) {
			_normal = 1;
		}
		else {
			_normal = -1;
		}
		return result;
	}

	vector<Polygon2D> Polygon2D::tessellate(vector<int>concaveVerticesIndices) {
		vector<Polygon2D>result;
		if (concaveVerticesIndices.size() == 0) {
			Polygon2D convexPolygon;
			convexPolygon.setExterior(this->getExterior());
			result.push_back(convexPolygon);
			return result;
		}
		bool find = false;
		int index2;
		int count = 0;
		while (!find && count < concaveVerticesIndices.size()) {
			int index = concaveVerticesIndices.at(count);
			Point2D tempPoint = m_vertices.at(index);
			vector<int>resultSortedPointsIdxArray;
		
			//resultSortedPointsIdxArray = getPointsIndexSortedByDistFromPoint(tempPoint);
			
			int count2 = 0;

			while (!find && count2 < resultSortedPointsIdxArray.size()) {
				index2 = resultSortedPointsIdxArray.at(count2);
				int prevIndex = index - 1;
				if (prevIndex < 0)
					prevIndex = resultSortedPointsIdxArray.size() - 1;
				int nextIndex = (index + 1) % resultSortedPointsIdxArray.size();
				
				if (index2 == prevIndex || index2 == nextIndex) {
					count2++;
					continue;
				}

				//check intersection with the polygon and this pair(index-index2)
				//if(intersectionWithSegment(index, index2)){count2++;countinue;}
				//vector<Polygon2D> splittedPolygons = splitPolygon(index, index2);
				//

			}


		}
		
		return result;
	
	}

	Polygon2D::Polygon2D() {}

	Polygon2D::~Polygon2D() {}


}

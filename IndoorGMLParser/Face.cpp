#include <iostream>
#include <vector>
#include <math.h>
#include "Face.h"
#include "point3d.h"
#include "Point2D.h"
#include "Polygon2D.h"
#include "LinearRing.h"
using namespace std;

namespace geometry {

	void Face::setVertexArray(vector<geometry::Vertex> arr) {
		vertexArray = arr;
	}
	void Face::addVertex(Vertex a) {
		vertexArray.push_back(a);
	}
	vector<Vertex> Face::getVertexArray() {
		return vertexArray;
	}
	indoorgml::Point3D Face::getNormal() {
		setNormal();
		return _normal;
	}
	void Face::setNormal() {
		calculateNormal();
	}
	indoorgml::Point3D Face::calculateNormal() {
		indoorgml::Point3D result;
		if (vertexArray.size() == 0)
			return result;
		for (int i = 0; i < vertexArray.size(); i++) {
			int prevIndex, nextIndex;
			indoorgml::Point3D startVec;
			indoorgml::Point3D endVec;
			if (i == 0) {
				prevIndex = vertexArray.size() - 1;
			}
			else {
				prevIndex = i - 1;
			}
			nextIndex = i + 1;
			if (nextIndex == vertexArray.size()) {
				nextIndex = 0;
			}
			startVec = vertexArray.at(i).getPosition() - vertexArray.at(prevIndex).getPosition();
			endVec = vertexArray.at(nextIndex).getPosition() - vertexArray.at(i).getPosition();

			startVec.unitary();
			endVec.unitary();

			indoorgml::Point3D crossProd = startVec.cross(endVec);
			crossProd.unitary();

			double scalarProd = startVec.scalar(endVec);
			double cosAlfa = scalarProd;
			
			if (cosAlfa > 1.0) {
				cosAlfa = 1.0;
			}
			else if (cosAlfa < -1.0) {
				cosAlfa = -1.0;
			}
			double alfa = acos(cosAlfa);
			indoorgml::Point3D tempnormal(crossProd.x*alfa, crossProd.y*alfa, crossProd.z*alfa);

			result = result + tempnormal;			
		}
		result.unitary();
		hasNormalValue = true;
		_normal = result;
		return result;
	}
	int Face::getBestFacePlaneTypeToProject() {
		int type = -1;

		double nx = abs(_normal.x);
		double ny = abs(_normal.y);
		double nz = abs(_normal.z);

		if (nz > nx && nz >= ny) {
			type = 0; // xy
		}
		else if (nx >= ny && nx >= nz) {
			type = 1; // yz
		}
		else if (ny > nx && ny >= nz) {
			type = 2;
		}

		return type;
	}
	Polygon2D Face::getProjectedPolygon() {
		Polygon2D result;			
		vector<geometry::Point2D>resultPoints2d;
		Point2D tempPoint;

		calculateNormal();
		int type = getBestFacePlaneTypeToProject();
		
		if (type == 0) {
			for (int i = 0; i < vertexArray.size(); i++) {
				
				if (_normal.z > 0) {
					tempPoint = geometry::Point2D(vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().y);
					tempPoint.originalPoint = vertexArray.at(i).getPosition();
					resultPoints2d.push_back(tempPoint);
				}
				else {
					tempPoint.x = vertexArray.at(i).getPosition().x;
					tempPoint.y = -1 * (vertexArray.at(i).getPosition().y);
					tempPoint.originalPoint = vertexArray.at(i).getPosition();
					resultPoints2d.push_back(tempPoint);
					
				}
			}
		}
		else if (type == 1) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (_normal.x > 0) {
					tempPoint = geometry::Point2D(vertexArray.at(i).getPosition().y, vertexArray.at(i).getPosition().z);
					tempPoint.originalPoint = vertexArray.at(i).getPosition();
					resultPoints2d.push_back(tempPoint);
				}
				else {
					tempPoint = geometry::Point2D(-1 * (vertexArray.at(i).getPosition().y), vertexArray.at(i).getPosition().z);
					tempPoint.originalPoint = vertexArray.at(i).getPosition();
					resultPoints2d.push_back(tempPoint);
				}
			}
		}
		else if (type == 2) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (_normal.y > 0) {
					tempPoint = geometry::Point2D(-1 * (vertexArray.at(i).getPosition().x), vertexArray.at(i).getPosition().z);
					tempPoint.originalPoint = vertexArray.at(i).getPosition();
					resultPoints2d.push_back(tempPoint);
				}
				else {
					tempPoint = geometry::Point2D(vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().z);
					tempPoint.originalPoint = vertexArray.at(i).getPosition();
					resultPoints2d.push_back(tempPoint);
				}
			}
		}
		//shared_ptr<geometry::LinearRing2D> ext;
		//ext->setVertices(resultPoints2d);
		//result.setExterior(ext);
		result.setVertices(resultPoints2d);
		return result;
	}

	void Face::calculateVerticesNormals() {
		
		if (!hasNormalValue) {
			calculateNormal();
		}

		for (int i = 0; i < vertexArray.size(); i++) {
			vertexArray.at(i).setNormal(_normal.x,_normal.y,_normal.z);
		}
	}

	vector<Triangle> Face::getTessellatedTriangles() {
		vector<Triangle> result;
		if (vertexArray.size() <= 3) {
			result = getTrianglesConvex();
			
			return result;
		}

		Polygon2D temppoly = getProjectedPolygon();
		vector<int>concavePointIndexList = temppoly.calculateNormal();
		vector<Polygon2D> convexPolygonList = temppoly.tessellate(concavePointIndexList);

		for (int i = 0; i < convexPolygonList.size(); i++) {
			Polygon2D tempConvexPolygon = convexPolygonList.at(i);

			if (tempConvexPolygon.getVertices().size() == 0)
				continue;
			Vertex v0, v1, v2;
			Triangle t;
			Point2D p0, p1, p2;
			p0 = tempConvexPolygon.getVertices().at(0);
			v0 = p0.originalPoint;
			for (int j = 1; j < tempConvexPolygon.getVertices().size() - 1; j++) {
				p1 = tempConvexPolygon.getVertices().at(j);
				p2 = tempConvexPolygon.getVertices().at(j + 1);
				v1 = p1.originalPoint;
				v2 = p2.originalPoint;

				t = Triangle(v0, v1, v2);
				result.push_back(t);
			}

		}
		return result;
	}
	Face::Face() {
		hasNormalValue = false;
	}
	vector<Triangle> Face::getTrianglesConvex() {
		vector<Triangle> result;

		if (vertexArray.size() == 0)
			return result;

		Vertex v0, v1, v2;
		Triangle t;
		v0 = vertexArray.at(0);
		for (int i = 1; i < vertexArray.size() - 1; i++) {
			v1 = vertexArray.at(i);
			v2 = vertexArray.at(i+1);
			t = Triangle(v0, v1, v2);

			result.push_back(t);
		}

		return result;
	}
	/*
	void Face::convertFromPolygon(shared_ptr<indoorgml::Polygon> p) {
		shared_ptr<indoorgml::LinearRing> ext = p->getExterior();

		for (int i = 0; i < ext->getVertices().size(); i++) {
			indoorgml::Point3D p3 = ext->getVertices().at(i);
			Vertex v;
			v.setPosition(p3);
			v.setVertexIndex(i);
			addVertex(v);
		}
	}
	*/
}	

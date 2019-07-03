#include <iostream>
#include <vector>
#include <math.h>
#include "Face.h"
#include "point3d.h"
#include "Point2D.h"
#include "Polygon2D.h"
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
		for (int i = 0; i < vertexArray.size(); i++) {
			int prevIndex;
			indoorgml::Point3D startVec;
			indoorgml::Point3D endVec;
			if (i == 0) {
				prevIndex = vertexArray.size() - 1;
			}
			else {
				prevIndex = i - 1;
			}
			startVec = vertexArray.at(prevIndex).getNormal();
			endVec = vertexArray.at(i).getNormal();

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
		int type = getBestFacePlaneTypeToProject();
		vector<geometry::Point2D>resultPoints2d;
		if (type == 0) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (_normal.z > 0) {
					resultPoints2d.push_back(geometry::Point2D(vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().y));
				}
				else {
					resultPoints2d.push_back(geometry::Point2D(vertexArray.at(i).getPosition().x, -vertexArray.at(i).getPosition().y));
				}
			}
		}
		else if (type == 1) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (_normal.x > 0) {
					resultPoints2d.push_back(geometry::Point2D(vertexArray.at(i).getPosition().y, vertexArray.at(i).getPosition().z));
				}
				else {
					resultPoints2d.push_back(geometry::Point2D(-vertexArray.at(i).getPosition().y, vertexArray.at(i).getPosition().z));
				}
			}
		}
		else if (type == 2) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (_normal.y > 0) {
					resultPoints2d.push_back(geometry::Point2D(-vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().z));
				}
				else {
					resultPoints2d.push_back(geometry::Point2D(vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().z));
				}
			}
		}
		shared_ptr<geometry::LinearRing2D> ext;
		ext->setVertices(resultPoints2d);
		result.setExterior(ext);
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

		//vector<Point2D>convexPoint = temppoly.calculateNormal();
		
	}
	Face::Face() {
		hasNormalValue = false;
	}
	vector<Triangle> Face::getTrianglesConvex() {
		vector<Triangle> result;
		return result;
	}
}	

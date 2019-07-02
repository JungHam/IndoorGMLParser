#include <iostream>
#include <vector>
#include <math.h>
#include "Face.h"
#include "point3d.h"
#include "Point2D.h"
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
		return normal;
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
		return result;
	}
	int Face::getBestFacePlaneTypeToProject() {
		int type = -1;

		double nx = abs(normal.x);
		double ny = abs(normal.y);
		double nz = abs(normal.z);

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
	indoorgml::Polygon Face::getProjectedPolygon() {
		indoorgml::Polygon result("");
		int type = getBestFacePlaneTypeToProject();
		vector<indoorgml::Point2D>resultPoints2d;
		if (type == 0) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (normal.z > 0) {
					resultPoints2d.push_back(indoorgml::Point2D(vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().y));
				}
				else {
					resultPoints2d.push_back(indoorgml::Point2D(vertexArray.at(i).getPosition().x, -vertexArray.at(i).getPosition().y));
				}
			}
		}
		else if (type == 1) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (normal.x > 0) {
					resultPoints2d.push_back(indoorgml::Point2D(vertexArray.at(i).getPosition().y, vertexArray.at(i).getPosition().z));
				}
				else {
					resultPoints2d.push_back(indoorgml::Point2D(-vertexArray.at(i).getPosition().y, vertexArray.at(i).getPosition().z));
				}
			}
		}
		else if (type == 2) {
			for (int i = 0; i < vertexArray.size(); i++) {
				if (normal.y > 0) {
					resultPoints2d.push_back(indoorgml::Point2D(-vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().z));
				}
				else {
					resultPoints2d.push_back(indoorgml::Point2D(vertexArray.at(i).getPosition().x, vertexArray.at(i).getPosition().z));
				}
			}
		}
		//result.setExterior();
	}
}

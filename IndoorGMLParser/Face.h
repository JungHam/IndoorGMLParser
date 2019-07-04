#pragma once
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Point3d.h"
#include "Polygon2D.h"
#include "Polygon.h"
#include "Triangle.h"

using namespace std;

namespace geometry {
	class Face {
		vector<Vertex>vertexArray;
		indoorgml::Point3D calculateNormal();
		indoorgml::Point3D _normal;
		bool hasNormalValue;
	public : 
		Face();
		void addVertex(Vertex a);
		void setVertexArray(vector<Vertex> arr);
		vector<Vertex> getVertexArray();
		indoorgml::Point3D getNormal();
		void setNormal();
		int getBestFacePlaneTypeToProject();
		Polygon2D getProjectedPolygon();
		void calculateVerticesNormals();
		vector<Triangle> getTessellatedTriangles();
		vector<Triangle> getTrianglesConvex();
		void convertFromPolygon(shared_ptr<indoorgml::Polygon> p);

	};

}
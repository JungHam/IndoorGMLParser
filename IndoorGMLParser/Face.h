#pragma once
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "point3d.h"
#include "polygon.h"
using namespace std;

namespace geometry {
	class Face {
		vector<Vertex>vertexArray;
		indoorgml::Point3D calculateNormal();
		indoorgml::Point3D normal;
	public : 
		
		void addVertex(Vertex a);
		void setVertexArray(vector<Vertex> arr);
		vector<Vertex> getVertexArray();
		indoorgml::Point3D getNormal();
		void setNormal();
		int getBestFacePlaneTypeToProject();
		indoorgml::Polygon getProjectedPolygon();
	};

}
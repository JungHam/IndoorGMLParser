#pragma once

#include <iostream>
#include <vector>
#include "point3d.h"

using namespace std;

namespace geometry {
	class Vertex {
		indoorgml::Point3D _position;
		indoorgml::Point3D _normal;
		int vertexIndex;

	public:
		Vertex();
		Vertex(indoorgml::Point3D position);
		
		void setNormal();
		indoorgml::Point3D getNormal();
		void setPosition(indoorgml::Point3D position);
		indoorgml::Point3D getPosition();
		void setVertexIndex(int i);
		int getVertexIndex();
		void unitary();
	};
}
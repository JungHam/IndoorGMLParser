#include <iostream>
#include "Vertex.h"

namespace geometry { 
	Vertex::Vertex() {}
	Vertex::Vertex(indoorgml::Point3D position) {
		_position = position;
	}

	void Vertex::setNormal(double x, double y, double z) {
		_normal = indoorgml::Point3D(x,y,z);
	}
	indoorgml::Point3D Vertex::getNormal() {
		return _normal;
	}
	void Vertex::setPosition(indoorgml::Point3D position) {
		_position = position;
	}
	indoorgml::Point3D Vertex::getPosition() {
		return _position;
	}
	void Vertex::setVertexIndex(int i) {
		vertexIndex = i;
	}
	int Vertex::getVertexIndex() {
		return vertexIndex;
	}
	void Vertex::unitary() {
		_position.unitary();
	}

}
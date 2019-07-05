#include "Triangle.h"

namespace geometry { 

	Triangle::Triangle() {}
	Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) {
		vertex0 = v1;
		vertex1 = v2;
		vertex2 = v3;
	}

	void Triangle::setVertices(Vertex v1, Vertex v2, Vertex v3) {
		vertex0 = v1;
		vertex1 = v2;
		vertex2 = v3;
	}
	void Triangle::assignVerticesIdx() {
		vertexIdx0 = vertex0.getVertexIndex();
		vertexIdx1 = vertex1.getVertexIndex();
		vertexIdx2 = vertex2.getVertexIndex();

	}
	int* Triangle::getIndicesArray() {
		int* arr = new int[3];
		arr[0] = vertexIdx0;
		arr[1] = vertexIdx1;
		arr[2] = vertexIdx2;
		return arr;
	}
	void Triangle::calculatePlaneNormal() {		
		_normal = getCrossProduct(0);
		_normal.unitary();
	}
	indoorgml::Point3D Triangle::getCrossProduct(int indexVertex) {
		indoorgml::Point3D currentPoint, prevPoint, nextPoint, result;

		if (indexVertex == 0) {
			currentPoint = vertex0.getPosition();
			prevPoint = vertex2.getPosition();
			nextPoint = vertex1.getPosition();
		}
		else if (indexVertex == 1) {
			currentPoint = vertex1.getPosition();
			prevPoint = vertex0.getPosition();
			nextPoint = vertex2.getPosition();
		}
		else if (indexVertex == 2) {
			currentPoint = vertex2.getPosition();
			prevPoint = vertex1.getPosition();
			nextPoint = vertex0.getPosition();
		}

		indoorgml::Point3D v1(currentPoint.x - prevPoint.x, currentPoint.y-prevPoint.y,currentPoint.z-prevPoint.z);
		indoorgml::Point3D v2(nextPoint.x-currentPoint.x, nextPoint.y - currentPoint.y, nextPoint.z - currentPoint.z);
		
		v1.unitary();
		v2.unitary();

		result = v1.cross(v2);

		return result;
		
	}
}
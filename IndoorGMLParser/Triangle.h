#pragma once

#include <iostream>
#include "Vertex.h"

namespace geometry {
	class Triangle {
		Vertex vertex0;
		Vertex vertex1;
		Vertex vertex2;

		int vertexIdx0;
		int vertexIdx1;
		int vertexIdx2;

		indoorgml::Point3D _normal;
		
	public:
		Triangle();
		Triangle(Vertex v1, Vertex v2, Vertex v3);
		void setVertices(Vertex v1, Vertex v2, Vertex v3);
		void assignVerticesIdx();
		int* getIndicesArray();
		void calculatePlaneNormal();
		indoorgml::Point3D getCrossProduct(int indexVertex);
	};
}
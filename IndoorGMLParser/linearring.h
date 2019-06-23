#pragma once

#include <string>
#include "AbstractFeatures.h"
#include "point3d.h"
#include <vector>

namespace indoorgml {

	class LinearRing : public AbstractFeatures {
	public:
		LinearRing(const std::string& id);
		LinearRing(const std::string& id, bool isExterior);

		bool isExterior() const;

		unsigned int size() const;

		const std::vector<Point3D>& getVertices() const;
		std::vector<Point3D>& getVertices();
		void setVertices(std::vector<Point3D> vertices);

		void addVertex(const Point3D& v);

		Point3D computeNormal() const;

		void forgetVertices();

	protected:
		bool m_exterior;

		std::vector<Point3D> m_vertices;
		
	};
}


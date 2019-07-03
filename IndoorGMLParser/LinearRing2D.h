#ifndef _LINEARRING2D_H_
#define _LINEARRING2D_H_

#pragma once

#include <string>
#include "AbstractFeatures.h"
#include "Point2D.h"
#include <vector>

namespace geometry {

	class LinearRing2D{
	public:
		LinearRing2D();
		//LinearRing2D(const std::string& id, bool isExterior);

		bool isExterior() const;

		unsigned int size() const;

		const std::vector<Point2D>& getVertices() const;
		std::vector<Point2D>& getVertices();
		void setVertices(std::vector<Point2D> vertices);

		void addVertex(const Point2D& v);

		Point2D computeNormal() const;

		void forgetVertices();

	protected:
		bool m_exterior;

		std::vector<Point2D> m_vertices;

	};
}

#endif
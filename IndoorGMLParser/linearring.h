#pragma once

#include <string>
#include "AbstractFeatures.h"
#include "point.hpp"
#include <vector>

namespace indoorgml {

	class LinearRing : public AbstractFeatures {
	public:
		LinearRing(const std::string& id, bool isExterior);

		bool isExterior() const;

		unsigned int size() const;

		const std::vector<TVec3d>& getVertices() const;
		std::vector<TVec3d>& getVertices();
		void setVertices(std::vector<TVec3d> vertices);

		void addVertex(const TVec3d& v);

		TVec3d computeNormal() const;

		void forgetVertices();

	protected:
		bool m_exterior;

		std::vector<TVec3d> m_vertices;
		
	};
}


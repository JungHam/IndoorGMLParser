#pragma once

#include "point.hpp"
#include "AbstractFeatures.h"
#include <memory>

#include <vector>

namespace indoorgml {

	class IndoorGMLFactory;

	/**
	* @brief The LineString class implements the gml:LineString object may also be used as a container of a single gml::Point
	*/
	class LineString : public AbstractFeatures {
		friend class IndoorGMLFactory;
	public:
		int getDimensions() const;

		const std::vector<TVec2d>& getVertices2D() const;
		const std::vector<TVec3d>& getVertices3D() const;

		std::vector<TVec2d>& getVertices2D();
		std::vector<TVec3d>& getVertices3D();

		void setVertices2D(const std::vector<TVec2d>& vertices);
		void setVertices3D(const std::vector<TVec3d>& vertices);

		void setDimensions(int dim);

	protected:
		LineString(const std::string& id);
		std::vector<TVec2d> m_vertices_2d;
		std::vector<TVec3d> m_vertices_3d;
		int m_dimensions;
	};

}
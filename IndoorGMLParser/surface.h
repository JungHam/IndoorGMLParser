#pragma once
#include <iostream>
#include "AbstractFeatures.h"
#include "LinearRing.h"

namespace indoorgml {
	class LineString;
	class Polygon;

	class Surface : public AbstractFeatures
	{
		friend class IndoorGMLFactory;
	public:

		bool hasExterior();
		bool hasInterior();
		const Polygon& getExterior() const;
		Polygon& getExterior();
		vector<Polygon&> getInterior();
		void addInterior(std::shared_ptr<Polygon>);
		//void deleteInterior();
		void setExterior(std::shared_ptr<Polygon>);
		void finish(bool optimize, std::shared_ptr<Logger> logger);
		Surface(const std::string& id);
		~Surface();


	protected:

		bool m_finished;
		unsigned int m_lod;

		std::vector<std::shared_ptr<LinearRing> > exterior;
		std::vector<std::shared_ptr<LinearRing>> interior;
	};
};
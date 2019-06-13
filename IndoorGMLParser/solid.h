#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include "AbstractFeatures.h"
#include "surface.h"
#include "logger.h"


namespace indoorgml {

	class LineString;
	class Polygon;

	class Solid : public AbstractFeatures
	{
		friend class IndoorGMLFactory;
	public:

		bool hasExterior();
		bool hasInterior();
		const Solid& getExterior() const;
		Solid& getExterior();
		vector<Surface&> getInterior();
		void addInterior(std::shared_ptr<Solid>);
		//void deleteInterior();
		void setExterior(std::shared_ptr<Surface>);
		void finish(bool optimize, std::shared_ptr<Logger> logger);
		Solid(const std::string& id);
		~Solid();


	protected:
		
		bool m_finished;
		unsigned int m_lod;

		std::vector<std::shared_ptr<Surface> > exterior;
		std::vector<std::shared_ptr<Solid>> interior;
	};

}

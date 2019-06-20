#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include "AbstractFeatures.h"
#include "logger.h"


namespace indoorgml {

	class LineString;
	class Polygon;
	class Surface;

	class Solid : public AbstractFeatures
	{
		friend class IndoorGMLFactory;
	public:

		bool hasExterior();
		bool hasInterior();
		const Solid& getExterior() const;
		vector<shared_ptr<Polygon>> getExterior();
		std::vector<std::shared_ptr<Solid>> getInterior();
		void addInterior(std::shared_ptr<Solid>);
		//void deleteInterior();
		void setExterior(vector<std::shared_ptr<Polygon>>);
		void finish(bool optimize, std::shared_ptr<Logger> logger);
		Solid(const std::string& id);

		~Solid();


	protected:
		
		bool m_finished;
		unsigned int m_lod;

		std::vector<std::shared_ptr<Polygon> > exterior;
		std::vector<std::shared_ptr<Solid>> interior;
	};

}

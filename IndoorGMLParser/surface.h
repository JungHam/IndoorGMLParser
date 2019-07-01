#ifndef _SURFACE_H_
#define _SURFACE_H_
#pragma once
#include <iostream>
#include "AbstractFeatures.h"
#include "LinearRing.h"
using namespace std;
namespace indoorgml {
	class LineString;
	class Polygon;

	class Surface : public AbstractFeatures
	{
		friend class IndoorGMLFactory;
	public:

		/*
		bool hasExterior();
		bool hasInterior();
		const Polygon& getExterior() const;
		Polygon& getExterior();
		vector<Polygon&> getInterior();
		void addInterior(std::shared_ptr<Polygon>);
		//void deleteInterior();
		void setExterior(std::shared_ptr<Polygon>);
		void finish(bool optimize);
		Surface(const std::string& id);
		~Surface();
		*/


	protected:

		bool m_finished;
		unsigned int m_lod;

		//shared_ptr<LinearRing> exterior;
		//shared_ptr<Polygon> polygonlist;
		//std::vector<shared_ptr<LinearRing>> interior;
	};
};
#endif
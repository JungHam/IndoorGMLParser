#include <iostream>
#include <vector>
#include "solid.h"

using namespace std;

namespace indoorgml {
	bool Solid::hasExterior(){
		if (exterior.size() == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	bool Solid::hasInterior() {
		if (interior.size() == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	const Solid& Solid::getExterior() const {	
	}
	vector<shared_ptr<Surface>> Solid::getExterior() {
		return exterior;
	}
	std::vector<std::shared_ptr<Solid>> Solid::getInterior() {
		return interior;
	}
	void Solid::addInterior(std::shared_ptr<Solid> s) {
		interior.push_back(s);
	}
	//void deleteInterior(){}
	void Solid::setExterior(vector<std::shared_ptr<Surface>> s) {
		exterior = s;
	}
	void Solid::finish(bool optimize, std::shared_ptr<Logger> logger) {}
	Solid::Solid(const std::string& id) : AbstractFeatures(id){}
	Solid::~Solid() {}
}
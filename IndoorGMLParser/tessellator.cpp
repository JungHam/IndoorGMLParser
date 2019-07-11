#include "tessellator.h"


vector<geometry::Triangle> tessellator::tessellate(indoorgml::Solid s) {
	vector<geometry::Triangle> result;
	
	vector<shared_ptr<indoorgml::Polygon>> exterior = s.getExterior();

	for (int i = 0; i < exterior.size(); i++) {
		vector<geometry::Triangle>temp;
		Face f = exterior.at(i)->convertFromPolygonToFace();
		temp = f.getTessellatedTriangles();
		result.insert(result.end(),temp.begin(),temp.end());
	}

	return result;
}
vector<geometry::Triangle> tessellator::tessellate(indoorgml::Polygon p) {
	vector<geometry::Triangle> result;

	Face f = p.convertFromPolygonToFace();
	result = f.getTessellatedTriangles();
	return result;
}
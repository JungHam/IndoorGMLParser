#pragma once

#include <iostream>
#include "Triangle.h"
#include "Solid.h"
#include "Polygon.h"
class tessellator {
public: 
	vector<geometry::Triangle> tessellate(indoorgml::Solid s);
	vector<geometry::Triangle> tessellate(indoorgml::Polygon p);
	
};
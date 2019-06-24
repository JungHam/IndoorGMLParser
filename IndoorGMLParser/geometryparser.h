#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>

#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/util/XMLString.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "linearring.h"
#include "polygon.h"
#include "solid.h"

namespace util {
	class GeometryParser {
	public:
		shared_ptr<indoorgml::LinearRing> parseLinearRing(xercesc::DOMNode* l);

		shared_ptr<indoorgml::Polygon> parsePolygon(xercesc::DOMNode* p);

		shared_ptr<indoorgml::Solid> parseSolid(xercesc::DOMNode* s);


	};

}

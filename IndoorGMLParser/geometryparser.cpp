#include "geometryparser.h"
#include "parserutil.h"

namespace util {
	shared_ptr<indoorgml::LinearRing> GeometryParser::parseLinearRing(DOMNode* l) {
		ParserUtil* parseHelper = new util::ParserUtil();
		shared_ptr<indoorgml::LinearRing> result = shared_ptr<indoorgml::LinearRing>(new indoorgml::LinearRing(parseHelper->getNamedAttribute(l->getAttributes(), "gml:id")));
		if (parseHelper->hasNamedChild(l, "gml:pos")) {
			double arr[3];
			int count = 0;
			vector<indoorgml::Point3D>pointList;
			for (int i = 0; i < l->getChildNodes()->getLength(); i++) {
				if (!parseHelper->isTextNode(l->getChildNodes()->item(i))) {
					//cout << parseHelper->changeXMLCh2str(l->getChildNodes()->item(i)->getTextContent()) << endl;
					string pointvalue = parseHelper->changeXMLCh2str(l->getChildNodes()->item(i)->getTextContent());
					stringstream ss(pointvalue);
					ss >> arr[0] >> arr[1] >> arr[2];
					//cout << arr[0] << " " << arr[1] << " " << arr[2] << endl;
					indoorgml::Point3D newPoint(arr);
					pointList.push_back(newPoint);
				}

			}
			result->setVertices(pointList);

		}
		else if (parseHelper->hasNamedChild(l, "gml:posList")) {
			//TODO: 
		}
		return result;
	}

	shared_ptr<indoorgml::Polygon> GeometryParser::parsePolygon(DOMNode* p) {
		ParserUtil* parseHelper = new util::ParserUtil();

		shared_ptr<indoorgml::Polygon> result = shared_ptr<indoorgml::Polygon>(new indoorgml::Polygon(parseHelper->getNamedAttribute(p->getAttributes(), "gml:id")));
		DOMNode* exterior = parseHelper->getNamedNode(p->getChildNodes(), "gml:exterior");
		if (parseHelper->hasNamedChild(exterior, "gml:LinearRing")) {
			result->setExterior(parseLinearRing(parseHelper->getNamedNode(exterior->getChildNodes(), "gml:LinearRing")));
		}
		else if (parseHelper->isMatchedNodeName(exterior, "gml:LineString")) {}
		return result;
	}


	shared_ptr<indoorgml::Solid> GeometryParser::parseSolid(DOMNode* s) {
		ParserUtil* parseHelper = new util::ParserUtil();
		shared_ptr<indoorgml::Solid> result = shared_ptr<indoorgml::Solid>(new indoorgml::Solid(parseHelper->getNamedAttribute(s->getAttributes(), "gml:id")));
		DOMNode* exterior = parseHelper->getNamedNode(s->getChildNodes(), "gml:exterior");
		DOMNode* shell = parseHelper->getNamedNode(exterior->getChildNodes(), "gml:Shell");
		vector<DOMNode*> surfaceMember = parseHelper->getNamedNodes(shell->getChildNodes(), "gml:surfaceMember");
		vector<DOMNode*> polygonlist;
		//get polygon
		for (int i = 0; i < surfaceMember.size(); i++) {
			DOMNode* p = parseHelper->getNamedNode(surfaceMember.at(i)->getChildNodes(), "gml:Polygon");
			polygonlist.push_back(p);
		}
		//parse polygon
		vector<shared_ptr<indoorgml::Polygon>>parsedPolygon;
		for (int i = 0; i < surfaceMember.size(); i++) {
			parsedPolygon.push_back(parsePolygon(polygonlist.at(i)));
		}
		result->setExterior(parsedPolygon);

		return result;
	}

}
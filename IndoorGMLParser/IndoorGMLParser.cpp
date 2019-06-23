// IndoorGMLParser.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/util/XMLString.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "parserutil.h"
#include "solid.h"
#include "polygon.h"
#include "linearring.h"
#include "point3d.h"


using namespace std;
using namespace xercesc;
using namespace util;


shared_ptr<indoorgml::LinearRing> parseLinearRing(DOMNode* l) {
	ParserUtil* parseHelper = new util::ParserUtil();
	shared_ptr<indoorgml::LinearRing> result = shared_ptr<indoorgml::LinearRing>(new indoorgml::LinearRing(parseHelper->getNamedAttribute(l->getAttributes(),"gml:id")));
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

shared_ptr<indoorgml::Polygon> parsePolygon(DOMNode* p) {
	ParserUtil* parseHelper = new util::ParserUtil();
	
	shared_ptr<indoorgml::Polygon> result = shared_ptr<indoorgml::Polygon>(new indoorgml::Polygon(parseHelper->getNamedAttribute(p->getAttributes(), "gml:id")));
	DOMNode* exterior = parseHelper->getNamedNode(p->getChildNodes(), "gml:exterior");
	if (parseHelper->hasNamedChild(exterior, "gml:LinearRing")) {
		result->setExterior(parseLinearRing(parseHelper->getNamedNode(exterior->getChildNodes(),"gml:LinearRing")));
	}
	else if (parseHelper->isMatchedNodeName(exterior, "gml:LineString")) {}
	return result;
}


shared_ptr<indoorgml::Solid> parseSolid(DOMNode* s){
	ParserUtil* parseHelper = new util::ParserUtil();
	shared_ptr<indoorgml::Solid> result = shared_ptr<indoorgml::Solid>(new indoorgml::Solid(parseHelper->getNamedAttribute(s->getAttributes(),"gml:id")));	
	DOMNode* exterior = parseHelper->getNamedNode(s->getChildNodes(),"gml:exterior");
	DOMNode* shell = parseHelper->getNamedNode(exterior->getChildNodes(),"gml:Shell");
	vector<DOMNode*> surfaceMember = parseHelper->getNamedNodes(shell->getChildNodes(),"gml:surfaceMember");
	vector<DOMNode*> polygonlist;
	//get polygon
	for (int i = 0; i < surfaceMember.size(); i++) {
		DOMNode* p = parseHelper->getNamedNode(surfaceMember.at(i)->getChildNodes(),"gml:Polygon");
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

int main(int argc, char* args[])
{
 
    try {
		XMLPlatformUtils::Initialize();
		XercesDOMParser* parser = new XercesDOMParser();
		ParserUtil* parseHelper = new util::ParserUtil();
		indoorgml::GeometryManager geomManager;
		ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
		parser->setErrorHandler(errHandler);
		parser->setIncludeIgnorableWhitespace(false);
		parser->setDoSchema(true);
		const char * xmlFile = "../samples/seouluniv21centry.gml";
        parser->parse(xmlFile);

		cout << xmlFile << ": parse OK" << endl;
		DOMDocument* dom = parser->getDocument();
		DOMElement* rootNode = dom->getDocumentElement();
		//cout << XMLString::transcode(rootNode->getTagName()) << endl;
		DOMNodeList* rootChild = rootNode->getChildNodes();
		
		DOMNode* primalSpaceFeatures = 0;
		DOMNode* multiLayeredGraph = 0;
		vector<DOMNode*> cellSpaceMember;
		vector<DOMNode*> cellSpaceBoundaryMember;

		//primalSpaceFeatures -> PrimalSpaceFeatures
		primalSpaceFeatures = parseHelper->getNamedNode(rootChild, "core:primalSpaceFeatures");
		primalSpaceFeatures = parseHelper->getNamedNode(primalSpaceFeatures->getChildNodes(), "core:PrimalSpaceFeatures");

		//multiLayeredGraph -> MultiLayeredGraph
		multiLayeredGraph = parseHelper->getNamedNode(rootChild, "core:multiLayeredGraph");
		multiLayeredGraph = parseHelper->getNamedNode(multiLayeredGraph->getChildNodes(), "core:MultiLayeredGraph");

		
		cellSpaceMember = parseHelper->getNamedNodes(primalSpaceFeatures->getChildNodes(),"core:cellSpaceMember");
		cellSpaceBoundaryMember = parseHelper->getNamedNodes(primalSpaceFeatures->getChildNodes(), "core:cellSpaceBoundaryMember");

		vector<DOMNode*>cellspacelist;
		vector<DOMNode*>cellspaceboundarylist;
		for (int i = 0; i < cellSpaceMember.size(); i++) {
			cellspacelist.push_back(parseHelper->getNamedNode(cellSpaceMember.at(i)->getChildNodes(),"core:CellSpace"));
		}

		for (int i = 0; i < cellSpaceBoundaryMember.size(); i++) {
			cellspaceboundarylist.push_back(parseHelper->getNamedNode(cellSpaceBoundaryMember.at(i)->getChildNodes(), "core:CellSpaceBoundary"));
		}

		vector<DOMNode*>solidList;
		vector<DOMNode*>surfaceList;
		
		for (int i = 0; i < cellspacelist.size(); i++) {
			DOMNode* cellSpace = cellspacelist.at(i);

			for (int j = 0; j < cellSpace->getChildNodes()->getLength(); j++) {
				if (parseHelper->isMatchedNodeName(cellSpace->getChildNodes()->item(j), "core:cellSpaceGeometry")) {
					solidList.push_back(cellSpace->getChildNodes()->item(j)->getChildNodes()->item(1)->getChildNodes()->item(1));
				}
				
			}
		}

		for (int i = 0; i < cellspaceboundarylist.size(); i++) {
			DOMNode* cellSpaceboundary = cellspaceboundarylist.at(i);

			for (int j = 0; j < cellSpaceboundary->getChildNodes()->getLength(); j++) {
				if (parseHelper->isMatchedNodeName(cellSpaceboundary->getChildNodes()->item(j), "core:cellSpaceBoundaryGeometry")) {
					surfaceList.push_back(cellSpaceboundary->getChildNodes()->item(j)->getChildNodes()->item(1)->getChildNodes()->item(1));
				}

			}
		}

		for (int i = 0; i < solidList.size(); i++) {
			DOMNamedNodeMap* list = solidList.at(i)->getAttributes();
			//parseHelper->getNamedAttribute(list,"gml:id");
			shared_ptr<indoorgml::Solid> result = parseSolid(solidList.at(i));
			geomManager.addSolid(result);
		}

		for (int i = 0; i < surfaceList.size(); i++) {
			DOMNamedNodeMap* list = surfaceList.at(i)->getAttributes();
			//parseHelper->getNamedAttribute(list, "gml:id");
			shared_ptr<indoorgml::Polygon> result = parsePolygon(surfaceList.at(i));
			geomManager.addPolygon(result);
		}

		cout << geomManager.getSolidsCount();

		delete parser;
		delete errHandler;
		delete parseHelper;

		XMLPlatformUtils::Terminate();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    } catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    }
	catch (const SAXParseException& ex) {
		cout << XMLString::transcode(ex.getMessage()) << endl;

	}
	catch (...) {
        cout << "Unexpected Exception \n";
        return -1;
    }

    
    return 0;
}


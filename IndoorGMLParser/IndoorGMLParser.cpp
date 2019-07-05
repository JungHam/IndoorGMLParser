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
#include "geometryparser.h"
#include "Polygon2D.h"
#include "Point2D.h"
#include "Triangle.h"

using namespace std;
using namespace xercesc;
using namespace util;
using namespace geometry;

int readDocument(const char* xmlFile){
	try {
		XMLPlatformUtils::Initialize();
		XercesDOMParser* parser = new XercesDOMParser();
		ParserUtil* parseHelper = new util::ParserUtil();
		GeometryParser* gmp = new util::GeometryParser();
		indoorgml::GeometryManager geomManager;
		ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
		parser->setErrorHandler(errHandler);
		parser->setIncludeIgnorableWhitespace(false);
		parser->setDoSchema(true);
		//const char * xmlFile = "../samples/seouluniv21centry.gml";
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

		//cellSpaceMember -> cellSpace & cellSpaceBoundaryMember -> cellSpaceBoundary
		cellSpaceMember = parseHelper->getNamedNodes(primalSpaceFeatures->getChildNodes(), "core:cellSpaceMember");
		cellSpaceBoundaryMember = parseHelper->getNamedNodes(primalSpaceFeatures->getChildNodes(), "core:cellSpaceBoundaryMember");

		vector<DOMNode*>cellspacelist;
		vector<DOMNode*>cellspaceboundarylist;
		for (int i = 0; i < cellSpaceMember.size(); i++) {
			cellspacelist.push_back(parseHelper->getNamedNode(cellSpaceMember.at(i)->getChildNodes(), "core:CellSpace"));
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
			shared_ptr<indoorgml::Solid> result = gmp->parseSolid(solidList.at(i));
			geomManager.addSolid(result);
		}

		for (int i = 0; i < surfaceList.size(); i++) {
			DOMNamedNodeMap* list = surfaceList.at(i)->getAttributes();
			//parseHelper->getNamedAttribute(list, "gml:id");
			shared_ptr<indoorgml::Polygon> result = gmp->parsePolygon(surfaceList.at(i));
			geomManager.addPolygon(result);
		}

		cout << geomManager.getSolidsCount();




		delete parser;
		delete errHandler;
		delete parseHelper;
		XMLPlatformUtils::Terminate();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return -1;
	}
	catch (const DOMException& toCatch) {
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

int main(int argc, char* args[])
{

	//const char * xmlFile = "../samples/seouluniv21centry.gml";
	//readDocument(xmlFile);
	vector<geometry::Point2D>testPoints;
	testPoints.push_back(geometry::Point2D(0, 0));
	testPoints.push_back(geometry::Point2D(2, 0));
	testPoints.push_back(geometry::Point2D(2, 1));
	testPoints.push_back(geometry::Point2D(1, 1));
	testPoints.push_back(geometry::Point2D(1, 2));
	testPoints.push_back(geometry::Point2D(0, 2));

	geometry::Polygon2D testPolygon;
	testPolygon.setVertices(testPoints);
	
	vector<int>concaveVerticesIndices = testPolygon.calculateNormal();
	//vector<geometry::Polygon2D>result;
	//result.at(0);

	vector<Polygon2D>result = testPolygon.tessellate(concaveVerticesIndices);
	
	

}


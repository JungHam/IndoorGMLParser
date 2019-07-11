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

vector<geometry::Triangle> tessellate(shared_ptr<indoorgml::Polygon> p) {
	vector<geometry::Triangle> result;
	Face f = p->convertFromPolygonToFace();
	result = f.getTessellatedTriangles();
	return result;
}


vector<geometry::Triangle> tessellate(indoorgml::Polygon p) {
	vector<geometry::Triangle> result;
	Face f = p.convertFromPolygonToFace();
	result = f.getTessellatedTriangles();
	return result;
}

vector<geometry::Triangle> tessellate(indoorgml::Solid s) {
	vector<geometry::Triangle> result;

	vector<shared_ptr<indoorgml::Polygon>> exterior = s.getExterior();

	for (int i = 0; i < exterior.size(); i++) {
		vector<geometry::Triangle>temp;
		Face f = exterior.at(i)->convertFromPolygonToFace();
		temp = f.getTessellatedTriangles();
		result.insert(result.end(), temp.begin(), temp.end());
	}

	return result;
}

vector<geometry::Triangle> tessellate(shared_ptr<indoorgml::Solid> s) {
	vector<geometry::Triangle> result;

	vector<shared_ptr<indoorgml::Polygon>> exterior = s->getExterior();

	for (int i = 0; i < exterior.size(); i++) {
		vector<geometry::Triangle>temp;
		Face f = exterior.at(i)->convertFromPolygonToFace();
		temp = f.getTessellatedTriangles();
		result.insert(result.end(), temp.begin(), temp.end());
	}

	return result;
}

int readDocument(const char* xmlFile, vector<geometry::Triangle>&result){
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
		cout << XMLString::transcode(rootNode->getTagName()) << endl;
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

		vector<geometry::Triangle>tessellatedResult;

		for (int i = 0; i < geomManager.getSolidsCount(); i++) {
			vector<geometry::Triangle>temp = tessellate(geomManager.getSolid(i));
			tessellatedResult.insert(tessellatedResult.end(),temp.begin(),temp.end());
		}

		for (int i = 0; i < geomManager.getPolygonsCount(); i++) {
			vector<geometry::Triangle> temp = tessellate(geomManager.getPolygon(i));
			tessellatedResult.insert(tessellatedResult.end(),temp.begin(),temp.end());
		}

		delete parser;
		delete errHandler;
		delete parseHelper;
		XMLPlatformUtils::Terminate();
		result = tessellatedResult;

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
	/*
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
	cout << result.size() << endl;

	*/
	const char * xmlFile = "../samples/sampleIndoorGML.gml";
	vector<geometry::Triangle>result;
	readDocument(xmlFile, result);

	cout << result.size();



}
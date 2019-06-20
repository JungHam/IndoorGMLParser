// IndoorGMLParser.cpp : Defines the entry point for the console application.
//
#pragma comment (lib,"../external/xercesc/lib/xerces-c_3.lib")
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
#include "point.hpp"

using namespace std;
using namespace xercesc;
using namespace util;

/*
XMLNode* getPolygon(XMLNode* xmlparent) {
XMLNode* result;
return result;
}

XMLNode* getGeometry(XMLNode* xmlparent) {

XMLNode* exterior = xmlparent->FirstChildElement("gml:exterior");
XMLNode* result;
return result;
}

*/



/*
XMLCh* changeStr2XMLCh(const string s) {
char cstr[s.size() + 1];
copy(s.begin(), s.end(), cstr);
return XMLString::transcode(cstr);
}
*/

//shared_ptr<Solid> parseSolid(DOMNode* s) {


shared_ptr<indoorgml::LinearRing> parseLinearRing(DOMNode* l) {
	ParserUtil* parseHelper = new util::ParserUtil();
	shared_ptr<indoorgml::LinearRing> result = shared_ptr<indoorgml::LinearRing>(new indoorgml::LinearRing());
	vector<TVec3> pointList;
	//DOMNode* result = 0;
	if (parseHelper->hasNamedChild(l, "gml:pos")) {
		<T> arr = new <T>[3];
		int count = 0;
		for (int i = 0; i < l->getChildNodes()->getLength(); i++) {
			if (!parseHelper->isTextNode(l->getChildNodes()->item(i))) {
				//arr[count] = stof(parseHelper->changeXMLCh2str(l->getChildNodes()->item(i)->getNodeValue()));
				cout << parseHelper->changeXMLCh2str(l->getChildNodes()->item(i)->getNodeValue())) << endl;
			}
		}
		//TVec3 newPoint = new TVec3(arr);

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
	for (int i = 0; i < surfaceMember.size(); i++) {
		DOMNode* p = parseHelper->getNamedNode(surfaceMember.at(i)->getChildNodes(),"gml:Polygon");
		//cout << parseHelper->changeXMLCh2str(p->getNodeName()) << endl;;
		polygonlist.push_back(p);
	}

	return result;
}

int main(int argc, char* args[])
{
 
    try {
		XMLPlatformUtils::Initialize();
		XercesDOMParser* parser = new XercesDOMParser();
		ParserUtil* parseHelper = new util::ParserUtil();

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

		//primalSpaceFeatures -> PrimalSpaceFeatures
		primalSpaceFeatures = parseHelper->getNamedNode(rootChild, "core:primalSpaceFeatures");
		primalSpaceFeatures = parseHelper->getNamedNode(primalSpaceFeatures->getChildNodes(), "core:PrimalSpaceFeatures");

		//multiLayeredGraph -> MultiLayeredGraph
		multiLayeredGraph = parseHelper->getNamedNode(rootChild, "core:multiLayeredGraph");
		multiLayeredGraph = parseHelper->getNamedNode(multiLayeredGraph->getChildNodes(), "core:MultiLayeredGraph");

		
		cellSpaceMember = parseHelper->getNamedNodes(primalSpaceFeatures->getChildNodes(),"core:cellSpaceMember");

		vector<DOMNode*>cellspacelist;

		for (int i = 0; i < cellSpaceMember.size(); i++) {
			cellspacelist.push_back(parseHelper->getNamedNode(cellSpaceMember.at(i)->getChildNodes(),"core:CellSpace"));
		}
		vector<DOMNode*>solidList;
		for (int i = 0; i < cellspacelist.size(); i++) {
			DOMNode* cellSpace = cellspacelist.at(i);

			//cellSpaceGeometry -> Geometry3D -> Solid
			for (int j = 0; j < cellSpace->getChildNodes()->getLength(); j++) {
				if (parseHelper->isMatchedNodeName(cellSpace->getChildNodes()->item(j), "core:cellSpaceGeometry")) {
					solidList.push_back(cellSpace->getChildNodes()->item(j)->getChildNodes()->item(1)->getChildNodes()->item(1));
				}
				
			}
		}

		for (int i = 0; i < solidList.size(); i++) {
			DOMNamedNodeMap* list = solidList.at(i)->getAttributes();
			parseHelper->getNamedAttribute(list,"gml:id");
			parseSolid(solidList.at(i));
		}



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


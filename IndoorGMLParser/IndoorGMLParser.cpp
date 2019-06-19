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

using namespace std;
using namespace xercesc;
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
bool isTextNode(DOMNode* node) {
	return (node->getNodeType() == DOMNode::TEXT_NODE);
}
bool isMatchedNodeName(DOMNode* node, string nodeType) {
	return(!strcmp(XMLString::transcode(node->getNodeName()), nodeType.c_str()));
}
string changeXMLCh2str(const XMLCh* x) {
	return XMLString::transcode(x);
}
string getNamedAttribute(DOMNamedNodeMap* list, string s) {
	string result;
	for (int j = 0; j < list->getLength(); j++) {
		if (isTextNode(list->item(j))) {
			continue;
		}
		if (isMatchedNodeName(list->item(j), s.c_str())) {
			result = changeXMLCh2str(list->item(j)->getNodeValue());
			cout << result << endl;
			break;
		}
	}
	return result;
}
DOMNode* getNamedNode(DOMNodeList* list, string s) {
	DOMNode* result = 0;
	for (int i = 0; i < list->getLength(); i++) {
		if (!isTextNode(list->item(i))) {
			if (isMatchedNodeName(list->item(i), s)) {
				result = list->item(i);
				break;
			}
		}
	}
	return result;
}

vector<DOMNode*> getNamedNodes(DOMNodeList* list, string s) {
	vector<DOMNode*>result;
	for (int i = 0; i < list->getLength(); i++) {
		if (!isTextNode(list->item(i))) {
			if (isMatchedNodeName(list->item(i), s)) {
				result.push_back(list->item(i));
				
			}
		}
	}
	return result;
}

vector<DOMNode*> getNamedNodes(vector<DOMNode*> list, string s) {
	vector<DOMNode*>result;
	for (int i = 0; i < list.size(); i++) {
		if (!isTextNode(list.at(i))) {
			if (isMatchedNodeName(list.at(i), s)) {
				result.push_back(list.at(i));

			}
		}
	}
	return result;
}

/*
XMLCh* changeStr2XMLCh(const string s) {
char cstr[s.size() + 1];
copy(s.begin(), s.end(), cstr);
return XMLString::transcode(cstr);
}
*/
int main(int argc, char* args[])
{
 
    try {
		XMLPlatformUtils::Initialize();
		XercesDOMParser* parser = new XercesDOMParser();
		//parser->setValidationScheme(XercesDOMParser::Val_Always);
		//parser->setDoNamespaces(true); // optional

		ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
		parser->setErrorHandler(errHandler);
		parser->setIncludeIgnorableWhitespace(false);
		parser->setDoSchema(true);
		const char * xmlFile = "../samples/seouluniv21centry.gml";
        parser->parse(xmlFile);

		cout << xmlFile << ": parse OK" << endl;
		DOMDocument* dom = parser->getDocument();
		DOMElement* rootNode = dom->getDocumentElement();
		cout << XMLString::transcode(rootNode->getTagName()) << endl;
		DOMNodeList* rootChild = rootNode->getChildNodes();
		
		DOMNode* primalSpaceFeatures = 0;
		DOMNode* multiLayeredGraph = 0;
		vector<DOMNode*> cellSpaceMember;

		//primalSpaceFeatures -> PrimalSpaceFeatures
		primalSpaceFeatures = getNamedNode(rootChild, "core:primalSpaceFeatures");
		primalSpaceFeatures = getNamedNode(primalSpaceFeatures->getChildNodes(), "core:PrimalSpaceFeatures"); 

		//multiLayeredGraph -> MultiLayeredGraph
		multiLayeredGraph = getNamedNode(rootChild, "core:multiLayeredGraph");
		multiLayeredGraph = getNamedNode(multiLayeredGraph->getChildNodes(), "core:MultiLayeredGraph");

		
		cellSpaceMember = getNamedNodes(primalSpaceFeatures->getChildNodes(),"core:cellSpaceMember");

		vector<DOMNode*>cellspacelist;

		for (int i = 0; i < cellSpaceMember.size(); i++) {
			cellspacelist.push_back(getNamedNode(cellSpaceMember.at(i)->getChildNodes(),"core:CellSpace"));
		}
		vector<DOMNode*>solidList;
		for (int i = 0; i < cellspacelist.size(); i++) {
			DOMNode* cellSpace = cellspacelist.at(i);

			//cellSpaceGeometry -> Geometry3D -> Solid
			for (int j = 0; j < cellSpace->getChildNodes()->getLength(); j++) {
				if (isMatchedNodeName(cellSpace->getChildNodes()->item(j), "core:cellSpaceGeometry")) { 
					solidList.push_back(cellSpace->getChildNodes()->item(j)->getChildNodes()->item(1)->getChildNodes()->item(1));
				}
				
			}
		}

		for (int i = 0; i < solidList.size(); i++) {
			DOMNamedNodeMap* list = solidList.at(i)->getAttributes();
			getNamedAttribute(list,"gml:id");

		}

		delete parser;
		delete errHandler;
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


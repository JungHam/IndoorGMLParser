// IndoorGMLParser.cpp : Defines the entry point for the console application.
//
#pragma comment (lib,"../external/xercesc/lib/xerces-c_3.lib")
#include "stdafx.h"

#include <iostream>
#include <map>
#include <vector>

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
		const char * xmlFile = "seouluniv21centry.gml";
        parser->parse(xmlFile);

		cout << xmlFile << ": parse OK" << endl;
		DOMDocument* dom = parser->getDocument();
		DOMElement* rootNode = dom->getDocumentElement();
		cout << XMLString::transcode(rootNode->getTagName()) << endl;
		DOMNodeList* rootChild = rootNode->getChildNodes();
		
		DOMNode* primalSpaceFeatures = 0;
		DOMNode* multiLayeredGraph = 0;
		DOMNodeList* cellSpaceMember = 0;

		for (int i = 0; i < rootChild->getLength(); i++) {
			DOMNode* tempChild = rootChild->item(i);
			//cout << XMLString::transcode(tempChild->getNodeName()) << endl;
			const char *primal = "core:primalSpaceFeatures";
			const char *multi = "core:multiLayeredGraph";
			cout << XMLString::transcode(tempChild->getNodeName()) << endl;
			//tempChild->getNodeName()
			//if(isIgnorableWhitespace())
			if (!strcmp(XMLString::transcode(tempChild->getNodeName()),primal)) {
				primalSpaceFeatures = tempChild->getChildNodes()->item(1);
				cout << XMLString::transcode(primalSpaceFeatures->getNodeName()) << endl;
			}
			else if (!strcmp(XMLString::transcode(tempChild->getNodeName()),multi)) {
				multiLayeredGraph = tempChild->getChildNodes()->item(1);
			}
		}

		
		cellSpaceMember = primalSpaceFeatures->getChildNodes();
		
		
		for (int i = 0; i < cellSpaceMember->getLength(); i++) {
			DOMNode* cellSpace = cellSpaceMember->item(i);
			const char* cell = "core:cellSpaceMember";
			if (!strcmp(XMLString::transcode(cellSpace->getNodeName()),cell )) {
				DOMNamedNodeMap* attributeList = cellSpace->getChildNodes()->item(1)->getAttributes();
				for (int j = 0; j < attributeList->getLength(); j++) {
					const char* gmlId = "gml:id";
					if (!strcmp(XMLString::transcode(attributeList->item(j)->getNodeName()), gmlId)) {
						cout << XMLString::transcode(attributeList->item(j)->getNodeValue()) << endl;;
					}
				}
			}
			
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


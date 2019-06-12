// IndoorGMLParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinyxml2.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using namespace tinyxml2;



XMLNode* getPolygon(XMLNode* xmlparent) {

}

XMLNode* getGeometry(XMLNode* xmlparent) {
	
	XMLNode* exterior = xmlparent->FirstChildElement("gml:exterior");

}

int main()
{
	cout << "Hello" << endl;
	XMLDocument doc;
	
	XMLError error = doc.LoadFile("seouluniv21centry.gml");
	XMLNode* indoorFeatures = doc.FirstChild();
	XMLNode* multiLayeredGraph = indoorFeatures->FirstChildElement("core:multiLayeredGraph");
	XMLNode* MultiLayeredGraph = indoorFeatures->FirstChildElement("core:MultiLayeredGraph");

	XMLNode* primalSpaceFeatures = indoorFeatures->FirstChildElement("core:primalSpaceFeatures");
	XMLNode* PrimalSpaceFeatures = primalSpaceFeatures->FirstChildElement("core:PrimalSpaceFeatures");
	XMLNode* cellSpaceMember = PrimalSpaceFeatures->FirstChildElement("core:cellSpaceMember");
	XMLNode* cellSpaecBoundaryMember = PrimalSpaceFeatures->FirstChildElement("core:cellSpaceBoundaryMember");

	map<string, XMLNode*>cellspacelist;
	map<string, XMLNode*>cellspaceboundarylist;

	map<string, XMLNode*>cellspaceGeometryList;
	map<string, XMLNode*>cellspaceboundaryGeometryList;
	
	
	while (cellSpaceMember != nullptr) {
		XMLElement* cellspace = cellSpaceMember->FirstChildElement("core:CellSpace");
		cout << cellspace->Attribute("gml:id") << endl;
		cellspacelist.insert(make_pair(cellspace->Attribute("gml:id"),cellspace));
		cellspaceGeometryList.insert());
		cellSpaceMember = cellSpaceMember->NextSiblingElement("core:cellSpaceMember");
	}

	cout << "end of the cellspace" << endl;

	while (cellSpaecBoundaryMember != nullptr) {
		XMLElement* cellspaceboundary = cellSpaecBoundaryMember->FirstChildElement("core:CellSpaceBoundary");
		cout << cellspaceboundary->Attribute("gml:id") << endl;
		cellspaceboundaryGeometryList.insert(make_pair(cellspaceboundary->FirstChildElement("core:cellSpaceBoundaryGeometry")->Attribute("gml:id"), cellspaceboundary->FirstChildElement("core:cellSpaceBoundaryGeometry")));
		cellspaceboundarylist.insert(make_pair(cellspaceboundary->Attribute("gml:id"), cellspaceboundary));
		cellSpaecBoundaryMember = cellSpaecBoundaryMember->NextSiblingElement("core:cellSpaceBoundaryMember");
	}
	
	

	
	
	

	return 0;
}


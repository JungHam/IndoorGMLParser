#pragma once

#include <string>

using namespace std;

namespace indoorgml {
	class AbstractFeatures {
	public:
		AbstractFeatures(string id);
		
		string getId();

		virtual ~AbstractFeatures();

	protected:

		string m_id;
	};
}
#include <sstream>
#include <iostream>
#include "AbstractFeatures.h"

namespace indoorgml {
	AbstractFeatures::AbstractFeatures(string id) : m_id(id) {
		if (m_id == "") {
			//uuid�� id random �ο�
		}
	}
	string AbstractFeatures::getId() {
		return m_id;
	}

	AbstractFeatures::~AbstractFeatures() {}
}


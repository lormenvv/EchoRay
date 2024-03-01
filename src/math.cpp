#include <cmath>
#include <glm/vec4.hpp>
#include <iostream>
#include <string>

bool equals(float a, float b) {
	if (abs(a - b) < 0.00001) {
		return true;
	}
	return false;
}

bool isEqual(glm::dvec4 v1, glm::dvec4 v2) {
	bool vecEqual = equals(v1.x, v2.x) && equals(v1.y, v2.y) && equals(v1.z, v2.z) && equals(v1.w, v2.w);
	std::cout << "V1 is equal to V2: " + std::to_string(vecEqual) + " \n";
	return equals(v1.x, v2.x) && equals(v1.y, v2.y) && equals(v1.z, v2.z) && equals(v1.w, v2.w);
}
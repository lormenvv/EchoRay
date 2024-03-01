#include "sphere.h"
#include "ray.h"


Sphere::Sphere() {
	origin = glm::dvec4(0, 0, 0, 1);
	radius = 1.0;
}


std::vector<double> intersect() {
	std::vector<double> intersections{ 4.0, 6.0 };
	return intersections;
}
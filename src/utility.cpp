#include "utility.h"

bool equals(float a, float b) {
	if (abs(a - b) < 0.00001) {
		return true;
	}
	return false;
}

bool isEqual(glm::dvec4 v1, glm::dvec4 v2) {
	return equals(v1.x, v2.x) && equals(v1.y, v2.y) && equals(v1.z, v2.z) && equals(v1.w, v2.w);
}

bool isEqual(glm::vec3 v1, glm::vec3 v2) {
	return equals(v1.x, v2.x) && equals(v1.y, v2.y) && equals(v1.z, v2.z);
}

void toString(glm::dvec4 v)
{
	std::cout << "X: " + std::to_string(v.x) + "\n Y: " + std::to_string(v.y) + "\n Z: "
	+ std::to_string(v.z) + "\n W: " + std::to_string(v.w) << std::endl;
}

std::vector<Intersection> intersect(Sphere sphere, Ray ray) {
	std::vector<Intersection> intersections;
	auto transRay = ray.transform(glm::inverse(sphere.getTransform()));
	auto sphereToRay = transRay.getOrigin() - glm::dvec4(0, 0, 0, 1);
	double a = glm::dot(transRay.getDirection(), transRay.getDirection());
	double b = 2 * glm::dot(transRay.getDirection(), sphereToRay);
	double c = glm::dot(sphereToRay, sphereToRay) - 1;

	double discriminant = b*b - 4 * a * c;

	if (discriminant < 0) { return intersections; }
	intersections.push_back(Intersection((-b - sqrt(discriminant)) / (2 * a), sphere));
	intersections.push_back(Intersection((-b + sqrt(discriminant)) / (2 * a), sphere));
	return intersections;
}

glm::dvec4 reflect(glm::dvec4 in, glm::dvec4 normal)
{
	return in - normal * 2.0 * glm::dot(in, normal);
}
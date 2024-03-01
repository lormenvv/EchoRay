#ifndef SPHERE_H
#define SPHERE_H

#include <glm/vec4.hpp>
#include <vector>
#include <random>
#include <string>
#include <iostream>

class Sphere {
public:
	Sphere();
private:
	glm::dvec4 origin;
	double radius;
};

std::vector<double> intersect();


#endif
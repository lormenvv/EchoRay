#ifndef UTILITY
#define UTILITY

#include <glm/vec4.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"

bool equals(float a, float b);
bool isEqual(glm::dvec4 v1, glm::dvec4 v2);
void toString(glm::dvec4 v);
std::vector<Intersection> intersect(Sphere sphere, Ray ray);

#endif
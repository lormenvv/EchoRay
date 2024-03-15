#ifndef UTILITY
#define UTILITY

#include <glm/vec4.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"
#include "pointlight.h"
#include "world.h"

bool equals(float a, float b);
bool isEqual(glm::dvec4 v1, glm::dvec4 v2);
bool isEqual(glm::vec3 v1, glm::vec3 v2);
void toString(glm::dvec4 v);
void toString(glm::dvec3 v);
std::vector<Intersection> intersect(Sphere sphere, Ray ray);

std::vector<Intersection> worldIntersect(World world, Ray ray);
glm::dvec4 reflect(glm::dvec4 in, glm::dvec4 normal);
glm::dvec3 lighting(Material material, PointLight light, glm::dvec4 position, glm::dvec4 eye, glm::dvec4 normal);
glm::u8vec3 toRGB(glm::dvec3 color);

#endif
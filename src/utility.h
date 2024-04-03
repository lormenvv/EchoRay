#ifndef UTILITY
#define UTILITY

#include <glm/vec4.hpp>
#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"
#include "raytracingstructs.h"
#include "world.h"

const double EPSILON = 0.00001;

bool equals(float a, float b);
bool isEqual(glm::dmat4 m1, glm::dmat4 m2);
bool isEqual(glm::dvec4 v1, glm::dvec4 v2);
bool isEqual(glm::vec3 v1, glm::vec3 v2);
void toString(glm::dvec4 v);
void toString(glm::dvec3 v);
std::vector<Intersection> intersect(Sphere sphere, Ray ray);
std::vector<Intersection> worldIntersect(World world, Ray ray);
Computations prepareComputations(Intersection intersection, Ray ray);
glm::dvec4 reflect(glm::dvec4 in, glm::dvec4 normal);
glm::dvec3 lighting(Material material, PointLight light, glm::dvec4 position, glm::dvec4 eye, glm::dvec4 normal, bool inShadow = false);
glm::dvec3 shadeHit(World world, Computations computation);
glm::dvec3 colorAt(World world, Ray ray);
bool isShadowed(World world, glm::dvec4 point);
glm::dmat4 viewTransform(glm::dvec4 from, glm::dvec4 to, glm::dvec4 up);
glm::u8vec3 toRGB(glm::dvec3 color);


#endif
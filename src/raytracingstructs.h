#ifndef RAYTRACINGSTRUCTS_H
#define RAYTRACINGSTRUCTS_H
#include "sphere.h"

struct PointLight
{
    glm::dvec3 intensity;
    glm::dvec4 position;
    bool isEqual(PointLight p) const
    {
        return intensity == p.intensity && position == p.position;
    }
};

struct Computations
{
    double t;
    Sphere object;
    glm::dvec4 point, eye, normal;
    bool inside;
    bool isEqual(Computations c) const
    {
        return t == c.t && object == c.object && point == c.point && eye == c.eye && normal == c.normal;
    }
};

#endif //RAYTRACINGSTRUCTS_H

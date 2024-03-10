//
// Created by david on 3/10/2024.
//

#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

struct PointLight
{
    glm::vec3 intensity;
    glm::dvec4 position;
};

#endif //POINTLIGHT_H

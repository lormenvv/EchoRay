#include "world.h"

World defaultWorld()
{
    auto defaultWorld = World();
    auto lights = std::vector<PointLight> {PointLight {glm::dvec3(1, 1, 1), glm::dvec4(-10, 10, -10, 1)}};
    defaultWorld.setLights(lights);
    auto s1 = Sphere();
    auto material = Material();
    material.setColor(glm::dvec3(0.8, 1.0, 0.6));
    material.setDiffuse(0.7);
    material.setSpecular(0.2);
    s1.setMaterial(material);

    auto s2 = Sphere();
    s2.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(0.5)));

    defaultWorld.setObjects(std::vector<Sphere>({s1, s2}));
    return defaultWorld;
}

void World::addLight(PointLight light)
{
    m_lights.push_back(light);
}

void World::addObject(Sphere object)
{
    m_objects.push_back(object);
}

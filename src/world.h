#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "pointlight.h"
#include "sphere.h"
#include "world.h"


class World {
public:
    World()
    {
        m_lights = std::vector<PointLight>();
        m_objects = std::vector<Sphere>();
    }
    std::vector<PointLight> getLights() const
    {
        return m_lights;
    }

    std::vector<Sphere> getObjects() const
    {
        return m_objects;
    }

    void setLights(std::vector<PointLight> lights)
    {
        m_lights = lights;
    }
    void setObjects(std::vector<Sphere> objects)
    {
        m_objects = objects;
    }
private:
    std::vector<PointLight> m_lights;
    std::vector<Sphere> m_objects;
};

World defaultWorld();



#endif //WORLD_H

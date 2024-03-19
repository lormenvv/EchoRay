#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "raytracingstructs.h"
#include "sphere.h"


class World {
public:
    World()
    {
        m_lights = std::vector<PointLight>();
        m_objects = std::vector<Sphere>();
    }
    void addLight(PointLight light);
    void addObject(Sphere object);
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

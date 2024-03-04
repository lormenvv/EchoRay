#ifndef HIT_H
#define HIT_H
#include <vector>
#include "sphere.h"

class Intersection {
public:
    Intersection()
    {
        m_t = -1;
    }
    Intersection(double t, const Sphere &sphere)
    {
        m_t = t;
        m_sphere = sphere;
    }
    double getT() const
    {
        return m_t;
    }
    Sphere getObject() const
    {
        return m_sphere;
    }

    bool operator==(const Intersection &rhs) const {
        //std::cout << m_t << std::endl;
        //std::cout << m_sphere.getOrigin().x << m_sphere.getOrigin().y << m_sphere.getOrigin().z << m_sphere.getRadius() << std::endl;
        return m_sphere == rhs.getObject() && m_t == rhs.getT();
    }

private:
    double m_t;
    Sphere m_sphere;
};

Intersection hit(std::vector<Intersection> intersections);




#endif //HIT_H

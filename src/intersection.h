#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <vector>
#include <algorithm>
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
        return m_sphere == rhs.getObject() && m_t == rhs.getT();
    }

    static void sort(std::vector<Intersection> &intersections) {
        std::sort(intersections.begin(), intersections.end(), [](const Intersection &lhs, const Intersection &rhs) {
            return lhs.getT() < rhs.getT();
        });
    }

private:
    double m_t;
    Sphere m_sphere;
};

Intersection hit(std::vector<Intersection> &intersections);




#endif //INTERSECTION_H

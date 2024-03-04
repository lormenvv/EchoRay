#include "intersection.h"

Intersection hit(std::vector<Intersection> &intersections)
{
    double lowestT = std::numeric_limits<double>::infinity();
    Intersection closestHit;
    for (auto intersection : intersections)
    {
        if (intersection.getT() < 0)
        {
            continue;
        }
        if (intersection.getT() < lowestT)
        {
            lowestT = intersection.getT();
            closestHit = intersection;
        }
    }
    return closestHit;
}


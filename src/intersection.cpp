#include "intersection.h"

Intersection hit(std::vector<Intersection> &intersections)
{
    Intersection::sort(intersections);
    Intersection closestHit = Intersection(-std::numeric_limits<double>::infinity(), Sphere());
    /* Because list is already sorted, and we know the lowest nonnegative t is the hit, we just return
     * the first t value that is nonnegative and then we can break */

    for (auto intersection : intersections)
    {
        if (intersection.getT() > 0)
        {
            closestHit = intersection;
            break;
        }
    }
    return closestHit;
}




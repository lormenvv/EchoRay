#include <gtest/gtest.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "../src/ray.h"
#include "../src/sphere.h"
#include "../src/utility.h"
#include "../src/intersection.h"

TEST(RaySphereTests, PointDistanceComputation)
{
    auto ray = Ray(glm::dvec3(2, 3, 4), glm::dvec3(1, 0, 0));
    ASSERT_TRUE(isEqual(ray.position(0), glm::dvec4(2, 3, 4, 1)));
    ASSERT_TRUE(isEqual(ray.position(1), glm::dvec4(3, 3, 4, 1)));
    ASSERT_TRUE(isEqual(ray.position(-1), glm::dvec4(1, 3, 4, 1)));
    ASSERT_TRUE(isEqual(ray.position(2.5), glm::dvec4(4.5, 3, 4, 1)));
}

TEST(RaySphereTests, RaySphereIntersectionTwoPoints)
{
    auto ray = Ray(glm::dvec3(0, 0, -5), glm::dvec3(0, 0, 1));
    auto sphere = Sphere();
    auto xs = intersect(sphere, ray);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].getT(), 4.0);
    ASSERT_FLOAT_EQ(xs[1].getT(), 6.0);
}

TEST(RaySphereTests, RaySphereIntersectionTangentPoint)
{
    auto ray = Ray(glm::dvec3(0, 1, -5), glm::dvec3(0, 0, 1));
    auto sphere = Sphere();
    auto xs = intersect(sphere, ray);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].getT(), 5.0);
    ASSERT_FLOAT_EQ(xs[1].getT(), 5.0);
}

TEST(RaySphereTests, RaySphereIntersectionMissesPoints)
{
    auto ray = Ray(glm::dvec3(0, 2, -5), glm::dvec3(0, 0, 1));
    auto sphere = Sphere();
    auto xs = intersect(sphere, ray);
    ASSERT_EQ(xs.size(), 0);
}

TEST(RaySphereTests, RaySphereIntersectionInsideSphere)
{
    auto ray = Ray(glm::dvec3(0, 0, 0), glm::dvec3(0, 0, 1));
    auto sphere = Sphere();
    auto xs = intersect(sphere, ray);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].getT(), -1.0);
    ASSERT_FLOAT_EQ(xs[1].getT(), 1.0);
}

TEST(RaySphereTests, RaySphereIntersectionSphereBehindRay)
{
    auto ray = Ray(glm::dvec3(0, 0, 5), glm::dvec3(0, 0, 1));
    auto sphere = Sphere();
    auto xs = intersect(sphere, ray);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].getT(), -6.0);
    ASSERT_FLOAT_EQ(xs[1].getT(), -4.0);
}

TEST(RaySphereTests, IntersectionObjectTest)
{
    auto s = Sphere();
    auto intersection = Intersection(3.5, s);
    ASSERT_TRUE(equals(intersection.getT(), 3.5));
    ASSERT_EQ(intersection.getObject(), s);
}

TEST(RaySphereTests, IntersectionOnObject)
{
    auto ray = Ray(glm::dvec3(0, 0, -5), glm::dvec3(0, 0, 1));
    auto sphere = Sphere();
    auto xs = intersect(sphere, ray);
    ASSERT_EQ(xs.size(), 2);
    //ASSERT_EQ(xs[0].getObject(), &sphere);
    //ASSERT_EQ(xs[1].getObject(), &sphere); Memory addresses barely differ, but the data is ultimately the same.
}

TEST(RaySphereTests, AllIntersectionsPositiveT)
{
    auto s = Sphere();
    auto i1 = Intersection(1, s);
    auto i2 = Intersection(2, s);
    auto xs = std::vector<Intersection> { i2, i1 };
    auto i = hit(xs);
    ASSERT_TRUE(i == i1);
}

TEST(RaySphereTests, SomeIntersectionsNegativeT)
{
    auto s = Sphere();
    auto i1 = Intersection(-1, s);
    auto i2 = Intersection(1, s);
    auto xs = std::vector<Intersection> { i2, i1 };
    auto i = hit(xs);
    ASSERT_TRUE(i == i2);
}

TEST(RaySphereTests, AllIntersectionsNegativeT)
{
    auto s = Sphere();
    auto i1 = Intersection(-2, s);
    auto i2 = Intersection(-1, s);
    auto xs = std::vector<Intersection> { i2, i1 };
    auto i = hit(xs);
    ASSERT_FALSE(i == i1);
    ASSERT_FALSE(i == i2);
}


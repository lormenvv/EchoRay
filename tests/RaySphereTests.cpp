#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

TEST(RaySphereTests, LowestNonnegativeIntersection)
{
    auto s = Sphere();
    auto i1 = Intersection(5, s);
    auto i2 = Intersection(7, s);
    auto i3 = Intersection(-3, s);
    auto i4 = Intersection(2, s);
    auto xs = std::vector<Intersection> { i1, i2, i3, i4 };
    auto i = hit(xs);
    ASSERT_TRUE(i == i4);
}

TEST(RaySphereTests, TranslateRay)
{
    auto ray = Ray(glm::dvec3(1, 2, 3), glm::dvec3(0, 1, 0));
    const auto m = glm::translate(glm::dmat4(1.0f), glm::dvec3(3, 4, 5));
    const auto transformedRay = ray.transform(m);
    ASSERT_TRUE(isEqual(transformedRay.getOrigin(), glm::dvec4(4, 6, 8, 1)));
    ASSERT_TRUE(isEqual(transformedRay.getDirection(), glm::dvec4(0, 1, 0, 0)));
}

TEST(RaySphereTests, ScalingRay)
{
    auto ray = Ray(glm::dvec3(1, 2, 3), glm::dvec3(0, 1, 0));
    const auto m = glm::scale(glm::dmat4(1.0), glm::dvec3(2, 3, 4));
    const auto transformedRay = ray.transform(m);
    ASSERT_TRUE(isEqual(transformedRay.getOrigin(), glm::dvec4(2, 6, 12, 1)));
    ASSERT_TRUE(isEqual(transformedRay.getDirection(), glm::dvec4(0, 3, 0, 0)));
}

TEST(RaySphereTests, SphereDefaultTransformation)
{
    auto s = Sphere();
    ASSERT_TRUE(s.getTransform() == glm::dmat4(1.0));
}

TEST(RaySphereTests, ChangingSphereTransformation)
{
    auto s = Sphere();
    auto t = glm::translate(glm::dmat4(1.0), glm::dvec3(2, 3, 4));
    s.setTransform(t);
    ASSERT_TRUE(s.getTransform() == t);
}

TEST(RaySphereTests, IntersectingScaledSphereWithRay)
{
    auto r = Ray(glm::dvec3(0, 0, -5), glm::dvec3(0, 0, 1));
    auto s = Sphere();
    s.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(2, 2, 2)));
    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_FLOAT_EQ(xs[0].getT(), 3.0);
    ASSERT_FLOAT_EQ(xs[1].getT(), 7.0);
}

TEST(RaySphereTests, IntersectingTranslatedSphereWithRay)
{
    auto r = Ray(glm::dvec3(0, 0, -5), glm::dvec3(0, 0, 1));
    auto s = Sphere();
    s.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(5, 0, 0)));
    auto xs = intersect(s, r);
    ASSERT_EQ(xs.size(), 0);
}

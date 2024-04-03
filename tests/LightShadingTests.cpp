#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/ray.h"
#include "../src/sphere.h"
#include "../src/utility.h"
#include "../src/intersection.h"
#include"../src/raytracingstructs.h"

TEST(LightShadingTests, NormalAtPointOnXAxis)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(1, 0, 0, 1));
    ASSERT_TRUE(n == glm::dvec4(1, 0, 0, 0));
}

TEST(LightShadingTests, NormalAtPointOnYAxis)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(0, 1, 0, 1));
    ASSERT_TRUE(n == glm::dvec4(0, 1, 0, 0));
}

TEST(LightShadingTests, NormalAtPointOnZAxis)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(0, 0, 1, 1));
    ASSERT_TRUE(n == glm::dvec4(0, 0, 1, 0));
}

TEST(LightShadingTests, NormalAtPointNonAxialPoint)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 1));
    ASSERT_TRUE(n == glm::dvec4(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 0));
}

TEST(LightShadingTests, NormalIsNormalized)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 1));
    ASSERT_TRUE(n == glm::normalize(n));
}

TEST(LightShadingTests, TranslatedSphereNormal)
{
    auto s = Sphere();
    s.setTransform(glm::translate(glm::dmat4(1), glm::dvec3(0, 1, 0)));
    auto n = s.normalAt(glm::dvec4(0, 1.70711, -0.70711, 1));
    ASSERT_TRUE(isEqual(n, glm::dvec4(0, 0.70711, -0.70711, 0)));
}

TEST(LightShadingTests, TransformedSphereNormal)
{
    auto s = Sphere();
    auto pi = glm::pi<float>();
    auto rotation = glm::rotate(glm::dmat4(1.0), glm::degrees(pi / 5.0), glm::dvec3(0, 0, 1));
    auto scaling = glm::scale(glm::dmat4(1.0), glm::dvec3(1, 0.5, 1));
    auto transform = scaling * rotation;
    s.setTransform(transform);
    auto n = s.normalAt(glm::dvec4(0, sqrt(2)/2, -sqrt(2)/2, 1));
    ASSERT_TRUE(isEqual(n, glm::dvec4(0, 0.97014, -0.24254, 0)));
}

TEST(LightShadingTests, VectorReflection45Degrees)
{
    auto v = glm::dvec4(1, -1, 0, 0);
    auto n = glm::dvec4(0, 1, 0, 0);
    auto r = reflect(v, n);
    ASSERT_TRUE(isEqual(r, glm::dvec4(1, 1, 0, 0)));
}

TEST(LightShadingTests, VectorReflectSlantedSurface)
{
    auto v = glm::dvec4(0, -1, 0, 0);
    auto n = glm::dvec4(sqrt(2)/2, sqrt(2)/2, 0, 0);
    auto r = reflect(v, n);
    ASSERT_TRUE(isEqual(r, glm::dvec4(1, 0, 0, 0)));
}

TEST(LightShadingTests, PointLightInstantiation)
{
    auto intensity = glm::dvec3(1, 1, 1);
    auto position = glm::dvec4(0, 0, 0, 1);
    auto light = PointLight {glm::vec3(1, 1, 1), glm::dvec4(0, 0, 0, 1)};
    ASSERT_TRUE(light.position == position);
    ASSERT_TRUE(light.intensity == intensity);
}

TEST(LightShadingTests, MaterialInstantiation)
{
    auto m = Material();
    ASSERT_TRUE(m.getColor() == glm::dvec3(1, 1, 1));
    ASSERT_FLOAT_EQ(m.getAmbient(), 0.1);
    ASSERT_FLOAT_EQ(m.getDiffuse(), 0.9);
    ASSERT_FLOAT_EQ(m.getSpecular(), 0.9);
    ASSERT_FLOAT_EQ(m.getShininess(), 200.0);
}

TEST(LightShadingTests, SphereDefaultMaterial)
{
    auto s = Sphere();
    auto m = s.getMaterial();
    ASSERT_TRUE(m == Material());
}

TEST(LightShadingTests, SphereAssignedMaterial)
{
    auto s = Sphere();
    auto m = s.getMaterial();
    m.setAmbient(1.0);
    s.setMaterial(m);
    ASSERT_TRUE(s.getMaterial() == m);
}

TEST(LightShadingTests, LightingWithEyeBetweenLightAndSurface)
{
    auto m = Material();
    auto position = glm::dvec4(0, 0, 0, 1);
    auto eyeVector = glm::dvec4(0, 0, -1, 0);
    auto normalVector = glm::dvec4(0, 0, -1, 0);
    auto intensity = glm::vec3(1, 1, 1);
    auto lightPosition = glm::dvec4(0, 0, -10, 1);
    auto light = PointLight {intensity, lightPosition};
    auto result = lighting(m, light, position, eyeVector, normalVector);
    ASSERT_TRUE(result == glm::dvec3(1.9, 1.9, 1.9));
}

TEST(LightShadingTests, EyeOffset45Degrees)
{
    auto m = Material();
    auto position = glm::dvec4(0, 0, 0, 1);
    auto eyeVector = glm::dvec4(0, sqrt(2)/2, -sqrt(2)/2, 0);
    auto normalVector = glm::dvec4(0, 0, -1, 0);
    auto intensity = glm::vec3(1, 1, 1);
    auto lightPosition = glm::dvec4(0, 0, -10, 1);
    auto light = PointLight {intensity, lightPosition};
    auto result = lighting(m, light, position, eyeVector, normalVector);
    ASSERT_TRUE(result == glm::dvec3(1.0, 1.0, 1.0));
}

TEST(LightShadingTests, LightOffset45Degrees)
{
    auto m = Material();
    auto position = glm::dvec4(0, 0, 0, 1);
    auto eyeVector = glm::dvec4(0, 0, -1, 0);
    auto normalVector = glm::dvec4(0, 0, -1, 0);
    auto intensity = glm::vec3(1, 1, 1);
    auto lightPosition = glm::dvec4(0, 10, -10, 1);
    auto light = PointLight {intensity, lightPosition};
    auto result = lighting(m, light, position, eyeVector, normalVector);
    ASSERT_TRUE(isEqual(result, glm::dvec3(0.7364, 0.7364, 0.7364)));
}

TEST(LightShadingTests, EyeInPathOfReflection)
{
    auto m = Material();
    auto position = glm::dvec4(0, 0, 0, 1);
    auto eyeVector = glm::dvec4(0, -sqrt(2)/2, -sqrt(2)/2, 0);
    auto normalVector = glm::dvec4(0, 0, -1, 0);
    auto intensity = glm::vec3(1, 1, 1);
    auto lightPosition = glm::dvec4(0, 10, -10, 1);
    auto light = PointLight {intensity, lightPosition};
    auto result = lighting(m, light, position, eyeVector, normalVector);
    ASSERT_TRUE(isEqual(result, glm::dvec3(1.6364, 1.6364, 1.6364)));
}

TEST(LightShadingTests, LightBehindSurface)
{
    auto m = Material();
    auto position = glm::dvec4(0, 0, 0, 1);
    auto eyeVector = glm::dvec4(0, 0, -1, 0);
    auto normalVector = glm::dvec4(0, 0, -1, 0);
    auto intensity = glm::vec3(1, 1, 1);
    auto lightPosition = glm::dvec4(0, 0, 10, 1);
    auto light = PointLight {intensity, lightPosition};
    auto result = lighting(m, light, position, eyeVector, normalVector);
    toString(result);
    ASSERT_TRUE(result == glm::dvec3(0.1, 0.1, 0.1));
}

//Shadowing Tests

TEST(LightShadingTests, LightingWithSurfaceInShadow)
{
    auto m = Material();
    auto position = glm::dvec4(0, 0, 0, 1);
    auto eyeVector = glm::dvec4(0, 0, -1, 0);
    auto normalVector = glm::dvec4(0, 0, -1, 0);
    auto intensity = glm::vec3(1, 1, 1);
    auto lightPosition = glm::dvec4(0, 0, -10, 1);
    auto light = PointLight {intensity, lightPosition};
    auto inShadow = true;
    auto result = lighting(m, light, position, eyeVector, normalVector, inShadow);
    ASSERT_TRUE(result == glm::dvec3(0.1, 0.1, 0.1));
}

TEST(LightShadingTests, PointLightCollinear)
{
    auto w = defaultWorld();
    auto p = glm::dvec4(0, 10, 0, 1);
    ASSERT_FALSE(isShadowed(w, p));
}

TEST(LightShadingTests, ObjectBetweenPointAndLight)
{
    auto w = defaultWorld();
    auto p = glm::dvec4(10, -10, 10, 1);
    ASSERT_TRUE(isShadowed(w, p));
}

TEST(LightShadingTests, ObjectBehindLight)
{
    auto w = defaultWorld();
    auto p = glm::dvec4(-20, 20, -20, 1);
    ASSERT_FALSE(isShadowed(w, p));
}

TEST(LightShadingTests, ObjectBehindPoint)
{
    auto w = defaultWorld();
    auto p = glm::dvec4(-2, 2, -2, 1);
    ASSERT_FALSE(isShadowed(w, p));
}

TEST(LightShadingTests, ShadeHitGivenIntersectionInShadow) {
    auto w = World();
    auto light = PointLight {glm::dvec3(1, 1, 1), glm::dvec4(0, 0, -10, 1)};
    w.setLights(std::vector<PointLight> {light});
    auto s1 = Sphere();
    auto s2 = Sphere();
    s2.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0, 0, 10)));
    w.setObjects(std::vector<Sphere> {s1, s2});
    auto r = Ray(glm::dvec4(0, 0, 5, 1), glm::dvec4(0, 0, 1, 0));
    auto i = Intersection(4, s2);
    auto computation = prepareComputations(i, r);
    auto c = shadeHit(w, computation);
    toString(c);
    ASSERT_TRUE(isEqual(c, glm::dvec3(0.1)));
}

TEST(LightShadingTests, HitShouldOffsetPoint) {
    auto r = Ray(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
    auto shape = Sphere();
    shape.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0, 0, 1)));
    auto i = Intersection(5, shape);
    auto computation = prepareComputations(i, r);
    ASSERT_TRUE(computation.overPoint.z < -EPSILON / 2);
    ASSERT_TRUE(computation.point.z > computation.overPoint.z);
}
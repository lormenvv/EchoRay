#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/ray.h"
#include "../src/sphere.h"
#include "../src/utility.h"
#include "../src/intersection.h"
#include"../src/pointlight.h"

TEST(LightShadingTests, NormalAtPointOnXAxis)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(1, 0, 0, 1));
    ASSERT_TRUE(isEqual(n, glm::dvec4(1, 0, 0, 0)));
}

TEST(LightShadingTests, NormalAtPointOnYAxis)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(0, 1, 0, 1));
    ASSERT_TRUE(isEqual(n, glm::dvec4(0, 1, 0, 0)));
}

TEST(LightShadingTests, NormalAtPointOnZAxis)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(0, 0, 1, 1));
    ASSERT_TRUE(isEqual(n, glm::dvec4(0, 0, 1, 0)));
}

TEST(LightShadingTests, NormalAtPointNonAxialPoint)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 1));
    ASSERT_TRUE(isEqual(n, glm::dvec4(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 0)));
}

TEST(LightShadingTests, NormalIsNormalized)
{
    auto s = Sphere();
    auto n = s.normalAt(glm::dvec4(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 1));
    ASSERT_TRUE(isEqual(n, glm::normalize(n)));
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
    auto intensity = glm::vec3(1, 1, 1);
    auto position = glm::dvec4(0, 0, 0, 1);
    auto light = PointLight {glm::vec3(1, 1, 1), glm::dvec4(0, 0, 0, 1)};
    ASSERT_TRUE(isEqual(light.position, position));
    ASSERT_TRUE(isEqual(light.intensity, intensity));
}

TEST(LightShadingTests, MaterialInstantiation)
{
    auto m = Material();
    ASSERT_TRUE(isEqual(m.getColor(), glm::vec3(1, 1, 1)));
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


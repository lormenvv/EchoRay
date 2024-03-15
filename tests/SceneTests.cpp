#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/ray.h"
#include "../src/sphere.h"
#include "../src/utility.h"
#include "../src/intersection.h"
#include "../src/pointlight.h"
#include "../src/world.h"


TEST(SceneTests, WorldCreate)
{
    auto w = World();
    ASSERT_FLOAT_EQ(w.getObjects().size(), 0);
    ASSERT_FLOAT_EQ(w.getLights().size(), 0);
}

TEST(SceneTests, DefaultWorldCreate)
{
    auto light = PointLight{glm::dvec3(1, 1, 1), glm::dvec4(-10, 10, -10, 1)};
    auto material = Material();
    material.setColor(glm::dvec3(0.8, 1.0, 0.6));
    material.setDiffuse(0.7);
    material.setSpecular(0.2);
    auto s1 = Sphere();
    s1.setMaterial(material);
    auto s2 = Sphere();
    s2.setTransform(glm::scale(glm::dmat4(1.0f), glm::dvec3(0.5, 0.5, 0.5)));
    auto w = defaultWorld();
    auto worldLight = w.getLights()[0];

    ASSERT_TRUE(worldLight.isEqual(light));
    ASSERT_EQ(w.getObjects(), std::vector<Sphere> ({s1, s2}));
}

TEST(SceneTests, IntersectWorldWithRay)
{
    auto w = defaultWorld();
    auto r = Ray(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
    auto xs = worldIntersect(w, r);
    ASSERT_FLOAT_EQ(xs.size(), 4);
    ASSERT_EQ(xs[0].getT(), 4);
    ASSERT_EQ(xs[1].getT(), 4.5);
    ASSERT_EQ(xs[2].getT(), 5.5);
    ASSERT_EQ(xs[3].getT(), 6);
}
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/ray.h"
#include "../src/sphere.h"
#include "../src/utility.h"
#include "../src/intersection.h"
#include "../src/raytracingstructs.h"
#include "../src/world.h"
#include "../src/camera.h"



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

TEST(SceneTests, PrecomputingIntersections)
{
    auto r = Ray(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
    auto sphere = Sphere();
    auto i = Intersection(4, sphere);
    auto computation = prepareComputations(i, r);
    ASSERT_TRUE(computation.t == i.getT());
    ASSERT_EQ(computation.object, i.getObject());
    ASSERT_EQ(computation.point, glm::dvec4(0, 0, -1, 1));
    ASSERT_EQ(computation.eye, glm::dvec4(0, 0, -1, 0));
    ASSERT_EQ(computation.normal, glm::dvec4(0, 0, -1, 0));
}

TEST(SceneTests, HitWhenIntersectionOccursOnOutside)
{
    auto r = Ray(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
    auto sphere = Sphere();
    auto i = Intersection(4, sphere);
    auto computations = prepareComputations(i, r);
    ASSERT_FALSE(computations.inside);
}

TEST(SceneTests, HitWhenIntersectionOccursOnInside)
{
    auto r = Ray(glm::dvec4(0, 0, 0, 1), glm::dvec4(0, 0, 1, 0));
    auto sphere = Sphere();
    auto i = Intersection(1, sphere);
    auto computation = prepareComputations(i, r);
    std::cout << glm::dot(computation.normal, computation.eye) << std::endl;
    ASSERT_TRUE(isEqual(computation.eye, glm::dvec4(0, 0, -1, 0)));
    ASSERT_TRUE(isEqual(computation.normal, glm::dvec4(0, 0, -1, 0)));
    ASSERT_TRUE(isEqual(computation.point, glm::dvec4(0, 0, 1, 1)));
    ASSERT_TRUE(computation.inside);
}

TEST(SceneTests, ShadingIntersection)
{
    auto w = defaultWorld();
    auto r = Ray(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
    auto shape = w.getObjects()[0];
    auto i = Intersection(4, shape);
    auto computation = prepareComputations(i, r);
    auto c = shadeHit(w, computation);
    ASSERT_TRUE(isEqual(c, glm::dvec3(0.38066, 0.47583, 0.2855)));
}

TEST(SceneTests, ShadingIntersectionFromInside)
{
    auto w = defaultWorld();
    auto light = PointLight {glm::dvec3(1, 1, 1), glm::dvec4(0, 0.25, 0, 1)};
    w.setLights(std::vector<PointLight> {light});
    auto r = Ray(glm::dvec4(0, 0, 0, 1), glm::dvec4(0, 0, 1, 0));
    auto shape = w.getObjects()[1];
    auto i = Intersection(0.5, shape);
    auto computation = prepareComputations(i, r);
    auto c = shadeHit(w, computation);
    toString(c);
    ASSERT_TRUE(isEqual(c, glm::dvec3(0.90498)));
}

TEST(SceneTests, ColorWhenRayMisses)
{
    auto w = defaultWorld();
    auto r = Ray(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 1, 0, 0));
    auto c = colorAt(w, r);
    ASSERT_TRUE(isEqual(c, glm::dvec3(0)));
}

TEST(SceneTests, ColorWhenRayHits)
{
    auto w = defaultWorld();
    auto r = Ray(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
    auto c = colorAt(w, r);
    ASSERT_TRUE(isEqual(c, glm::dvec3(0.38066, 0.47583, 0.2855)));
}

TEST(SceneTests, ColorWithIntersectionBehindRay)
{
    auto w = defaultWorld();
    auto outer = w.getObjects()[0];
    auto inner = w.getObjects()[1];
    auto outerMaterial = outer.getMaterial();
    auto innerMaterial = inner.getMaterial();
    innerMaterial.setAmbient(1);
    outerMaterial.setAmbient(1);
    outer.setMaterial(outerMaterial);
    inner.setMaterial(innerMaterial);
    w.setObjects(std::vector<Sphere> { outer, inner });
    auto r = Ray(glm::dvec4(0, 0, 0.75, 1), glm::dvec4(0, 0, -1, 0));
    auto c = colorAt(w, r);
    ASSERT_TRUE(isEqual(c, inner.getMaterial().getColor()));
}

TEST(SceneTests, DefaultOrientationMatrix)
{
    auto from = glm::dvec4(0, 0, 0, 1);
    auto to = glm::dvec4(0, 0, -1, 1);
    auto up = glm::dvec4(0, 1, 0, 0);
    auto t = viewTransform(from, to, up);
    ASSERT_EQ(t, glm::dmat4(1));
}

TEST(SceneTests, PositiveZViewTransformationMatrix)
{
    auto from = glm::dvec4(0, 0, 0, 1);
    auto to = glm::dvec4(0, 0, 1, 1);
    auto up = glm::dvec4(0, 1, 0, 0);
    auto t = viewTransform(from, to, up);
    ASSERT_EQ(t, glm::scale(glm::dmat4(1), glm::dvec3(-1, 1, -1)));
}

TEST(SceneTests, MoveWorldViewTransformationMatrix)
{
    auto from = glm::dvec4(0, 0, 8, 1);
    auto to = glm::dvec4(0, 0, 0, 1);
    auto up = glm::dvec4(0, 1, 0, 0);
    auto t = viewTransform(from, to, up);
    ASSERT_EQ(t, glm::translate(glm::dmat4(1), glm::dvec3(0, 0, -8)));
}

TEST(SceneTests, ArbitraryViewTransformation)
{
    auto from = glm::dvec4(1, 3, 2, 1);
    auto to = glm::dvec4(4, -2, 8, 1);
    auto up = glm::dvec4(1, 1, 0, 0);
    auto t = viewTransform(from, to, up);
    ASSERT_TRUE(isEqual(t, glm::dmat4x4(-0.50709, 0.50709, 0.67612, -2.36643,
                               0.76772, 0.60609, 0.12122, -2.82843,
                               -0.35857, 0.59761, -0.71714, 0,
                               0, 0, 0, 0)));
}

TEST(SceneTests, ConstructingCamera)
{
    auto hSize = 160;
    auto vSize = 120;
    auto fieldOfView = glm::pi<double>() / 2;
    auto c = Camera(hSize, vSize, fieldOfView);
    ASSERT_FLOAT_EQ(c.getHSize(), 160);
    ASSERT_FLOAT_EQ(c.getVSize(), 120);
    ASSERT_FLOAT_EQ(c.getFieldOfView(), glm::pi<double>() / 2);
    ASSERT_TRUE(isEqual(c.getTransform(), glm::dmat4(1)));
}

TEST(SceneTests, PixelSizeHorizontalCanvas)
{
    auto c = Camera(200, 125, glm::pi<double>() / 2);
    ASSERT_FLOAT_EQ(c.getPixelSize(), 0.01);
}

TEST(SceneTests, PixelSizeVerticalCanvas)
{
    auto c = Camera(125, 200, glm::pi<double>() / 2);
    ASSERT_FLOAT_EQ(c.getPixelSize(), 0.01);
}

TEST(SceneTests, RayThroughCenterOfCanvas)
{
    auto c = Camera(201, 101, glm::pi<double>() / 2);
    auto r = c.rayForPixel(100, 50);
    ASSERT_TRUE(isEqual(r.getOrigin(), glm::dvec4(0, 0, 0, 1)));
    ASSERT_TRUE(isEqual(r.getDirection(), glm::dvec4(0, 0, -1, 0)));
}

TEST(SceneTests, RayThroughCornerOfCanvas)
{
    auto c = Camera(201, 101, glm::pi<double>() / 2);
    auto r = c.rayForPixel(0, 0);
    ASSERT_TRUE(isEqual(r.getOrigin(), glm::dvec4(0, 0, 0, 1)));
    ASSERT_TRUE(isEqual(r.getDirection(), glm::dvec4(0.66519, 0.33259, -0.66851, 0)));
}

TEST(SceneTests, RayWhenCameraIsTransformed)
{
    auto c = Camera(201, 101, glm::pi<double>() / 2);
    auto rotationY = glm::rotate(glm::dmat4(1.0), glm::pi<double>() / 4, glm::dvec3(0, 1, 0));
    auto translation = glm::translate(glm::dmat4(1.0), glm::dvec3(0, -2, 5));
    auto transform = rotationY * translation;
    c.setTransform(transform);
    auto r = c.rayForPixel(100, 50);
    ASSERT_TRUE(isEqual(r.getOrigin(), glm::dvec4(0, 2, -5, 1)));
    ASSERT_TRUE(isEqual(r.getDirection(), glm::dvec4(sqrt(2)/2, 0, -sqrt(2)/2, 0)));
}
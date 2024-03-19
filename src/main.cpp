#include <iostream>
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"


int main()
{
    const int hSize = 600;
    const int vSize = 600;
    auto window = sf::RenderWindow{ { hSize, vSize }, "EchoRay" };

    //Chapter 7 Challenge
    auto w = defaultWorld();
    auto c = Camera(hSize, vSize, glm::pi<double>()/3);
    c.setTransform(viewTransform(glm::dvec4(0, 1.5, -5, 1), glm::dvec4(0, 1, 0, 1), glm::dvec4(0, 1, 0, 0)));

    auto floor = Sphere();
    floor.setTransform(glm::scale(glm::dmat4(1), glm::dvec3(10, 0.01, 10)));
    auto floorMaterial = Material();
    floorMaterial.setColor(glm::dvec3(1, 0.9, 0.9));
    floorMaterial.setSpecular(0);
    floor.setMaterial(floorMaterial);

    auto leftWall = Sphere();
    auto leftWallTranslation = glm::translate(glm::dmat4(1), glm::dvec3(0, 0, 5));
    auto leftWallRotationY = glm::rotate(glm::dmat4(1), -glm::pi<double>() / 4, glm::dvec3(0, 1, 0));
    auto leftWallRotationX = glm::rotate(glm::dmat4(1), glm::pi<double>() / 2, glm::dvec3(1, 0, 0));
    auto leftWallScale = glm::scale(glm::dmat4(1), glm::dvec3(10, 0.01, 10));
    auto leftWallTransform = leftWallTranslation * leftWallRotationY * leftWallRotationX * leftWallScale;
    leftWall.setTransform(leftWallTransform);
    leftWall.setMaterial(floorMaterial);

    auto rightWall = Sphere();
    auto rightWallTranslation = glm::translate(glm::dmat4(1), glm::dvec3(0, 0, 5));
    auto rightWallRotationY = glm::rotate(glm::dmat4(1), glm::pi<double>() / 4, glm::dvec3(0, 1, 0));
    auto rightWallRotationX = glm::rotate(glm::dmat4(1), glm::pi<double>() / 2, glm::dvec3(1, 0, 0));
    auto rightWallScale = glm::scale(glm::dmat4(1), glm::dvec3(10, 0.01, 10));
    auto rightWallTransform = rightWallTranslation * rightWallRotationY * rightWallRotationX * rightWallScale;
    rightWall.setTransform(rightWallTransform);
    rightWall.setMaterial(floorMaterial);

    auto middle = Sphere();
    middle.setTransform(glm::translate(glm::dmat4(1), glm::dvec3(-0.5, 1, 0.5)));
    auto middleMaterial = Material();
    middleMaterial.setColor(glm::dvec3(0.1, 1, 0.5));
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);
    middle.setMaterial(middleMaterial);

    auto right = Sphere();
    right.setTransform(glm::translate(glm::dmat4(1), glm::dvec3(1.5, 0.5, -0.5)) * glm::scale(glm::dmat4(1), glm::dvec3(0.5, 0.5, 0.5)));
    auto rightMaterial = Material();
    rightMaterial.setColor(glm::dvec3(0.5, 1, 0.1));
    rightMaterial.setDiffuse(0.7);
    rightMaterial.setSpecular(0.3);
    right.setMaterial(rightMaterial);

    auto left = Sphere();
    left.setTransform(glm::translate(glm::dmat4(1), glm::dvec3(-1.5, 0.33, -0.75)) * glm::scale(glm::dmat4(1), glm::dvec3(0.33, 0.33, 0.33)));
    auto leftMaterial = Material();
    leftMaterial.setColor(glm::dvec3(1, 0.8, 0.1));
    leftMaterial.setDiffuse(0.7);
    leftMaterial.setSpecular(0.3);
    left.setMaterial(leftMaterial);

    auto objects = std::vector<Sphere>({floor, rightWall, leftWall, middle, right, left});

    w.setObjects(objects);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        for (int y = 0; y < vSize; y++)
        {
            for (int x = 0; x < hSize; x++)
            {
                auto color = render(c, w, x, y);
                sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                rectangle.setPosition(x, y);
                rectangle.setFillColor({color.r, color.g, color.b});
                window.draw(rectangle);
            }
        }
        window.display();
    }
}

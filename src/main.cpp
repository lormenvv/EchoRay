#include <iostream>
#include <SFML/Graphics.hpp>

#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "intersection.h"


int main()
{
    const int canvasPixels = 400;
    auto window = sf::RenderWindow{ { canvasPixels, canvasPixels }, "EchoRay" };
    auto red = sf::Color::Red;
    auto shape = Sphere();
    auto rayOrigin = glm::dvec4(0, 0, -5, 1);
    auto wallSize = 7.0;
    auto pixelSize = wallSize / canvasPixels;
    auto half = wallSize / 2;

    //light and shading challenge
    auto material = Material();
    material.setColor(glm::dvec3(0.1, 0.4, 1));
    shape.setMaterial(material);
    toString(shape.getMaterial().getColor());

    auto lightPosition = glm::dvec4(-10, 10, -10, 1);
    auto lightColor = glm::dvec3(1 , 1, 1);
    auto pointLight = PointLight {lightColor, lightPosition};

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
        for (int y = 0; y < canvasPixels; y++)
        {
            auto worldY = half - pixelSize * y;
            for (int x = 0; x < canvasPixels; x++)
            {
                auto worldX = -half + pixelSize * x;
                auto wallZ = 10;
                auto position = glm::dvec4(worldX, worldY, wallZ, 1);
                auto r = Ray(rayOrigin, glm::normalize(position - rayOrigin));
                auto xs = intersect(shape, r);

                if (hit(xs).getT() != -std::numeric_limits<double>::infinity())
                {
                    auto point = r.position(hit(xs).getT());
                    auto normal = hit(xs).getObject().normalAt(point);
                    auto eye = -r.getDirection();
                    auto color = lighting(hit(xs).getObject().getMaterial(), pointLight, point, eye, normal) * 255.0;
                    sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                    rectangle.setPosition(x, y);
                    if (color.x > 255.0)
                    {
                        color.x = 255.0;
                    }
                    if (color.y > 255.0)
                    {
                        color.y = 255.0;
                    }
                    if (color.z > 255.0)
                    {
                        color.z = 255.0;
                    }
                    rectangle.setFillColor({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)});
                    window.draw(rectangle);
                }
            }
        }
        window.display();
    }
}

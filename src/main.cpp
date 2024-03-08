#include <iostream>
#include <SFML/Graphics.hpp>

#include "ray.h"
#include "sphere.h"
#include "utility.h"


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
                    sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                    rectangle.setPosition(x, y);
                    rectangle.setFillColor(red);
                    window.draw(rectangle);
                }
            }
        }
        window.display();
    }
}

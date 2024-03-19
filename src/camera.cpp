#include <iostream>
#include "camera.h"
#include "utility.h"


double Camera::calculatePixelSize()
{
    auto halfView = glm::tan(m_fieldOfView / 2);
    auto aspect = (double)m_hSize / m_vSize;
    if (aspect >= 1)
    {
        m_halfWidth = halfView;
        m_halfHeight = halfView / aspect;
    }
    else
    {
        m_halfWidth = halfView * aspect;
        m_halfHeight = halfView;
    }

    return (m_halfWidth * 2) / m_hSize;
}

Ray Camera::rayForPixel(int px, int py)
{
    auto xOffset = (px + 0.5) * m_pixelSize;
    auto yOffset = (py + 0.5) * m_pixelSize;
    auto worldX = m_halfWidth - xOffset;
    auto worldY = m_halfHeight - yOffset;
    auto pixel = glm::inverse(m_transform) * glm::dvec4(worldX, worldY, -1, 1);
    auto origin = glm::inverse(m_transform) * glm::dvec4(0, 0, 0, 1);
    auto direction = glm::normalize(pixel - origin);

    return Ray(origin, direction);
}

glm::u8vec3 render(Camera camera, World world, int x, int y)
{
    auto ray = camera.rayForPixel(x, y);
    auto color = toRGB(colorAt(world, ray));
    return color;
}

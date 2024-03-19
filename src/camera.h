#ifndef CAMERA_H
#define CAMERA_H
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include "ray.h"
#include "world.h"

class Camera {
public:
    Camera(unsigned int hSize, unsigned int vSize, double fieldOfView)
    {
        m_hSize = hSize;
        m_vSize = vSize;
        m_fieldOfView = fieldOfView;
        m_transform = glm::dmat4(1);
        m_pixelSize = calculatePixelSize();
    }

    unsigned int getHSize()
    {
        return m_hSize;
    }

    unsigned int getVSize()
    {
        return m_vSize;
    }

    double getFieldOfView()
    {
        return m_fieldOfView;
    }

    glm::dmat4 getTransform()
    {
        return m_transform;
    }

    double getPixelSize()
    {
        return m_pixelSize;
    }

    double getHalfWidth()
    {
        return m_halfWidth;
    }

    double getHalfHeight()
    {
        return m_halfHeight;
    }

    void setTransform(glm::dmat4 transform)
    {
        m_transform = transform;
    }
    Ray rayForPixel(int px, int py);

private:
    unsigned int m_hSize, m_vSize;
    double m_fieldOfView;
    glm::dmat4 m_transform;
    double m_halfWidth, m_halfHeight, m_pixelSize;
    double calculatePixelSize();
};
glm::u8vec3 render(Camera camera, World world, int x, int y);



#endif //CAMERA_H

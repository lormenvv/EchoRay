#ifndef MATERIAL_H
#define MATERIAL_H
#include "glm/vec3.hpp"

class Material
{
public:
    Material()
    {
        m_color = glm::dvec3(1, 1, 1);
        m_ambient = 0.1;
        m_diffuse = 0.9;
        m_specular = 0.9;
        m_shininess = 200.0;
    }
    Material(glm::dvec3 color, double ambient, double diffuse, double specular, double shininess)
    {
        m_color = color;
        m_ambient = ambient;
        m_diffuse = diffuse;
        m_specular = specular;
        m_shininess = shininess;
    }
    bool operator==(const Material& other) const
    {
        return m_color == other.getColor() && m_ambient == other.getAmbient() && m_diffuse == other.getDiffuse() &&
            m_specular == other.getSpecular() && m_shininess == other.getShininess();
    }
    glm::dvec3 getColor() const
    {
        return m_color;
    }
    double getAmbient() const
    {
        return m_ambient;
    }
    double getDiffuse() const
    {
        return m_diffuse;
    }
    double getSpecular() const
    {
        return m_specular;
    }
    double getShininess() const
    {
        return m_shininess;
    }
    void setColor(glm::dvec3 color)
    {
        m_color = color;
    }
    void setAmbient(double ambient)
    {
        m_ambient = ambient;
    }
    void setDiffuse(double diffuse)
    {
        m_diffuse = diffuse;
    }
    void setSpecular(double specular)
    {
        m_specular = specular;
    }
    void setShininess(double shininess)
    {
        m_shininess = shininess;
    }
private:
    glm::dvec3 m_color{};
    double m_ambient, m_diffuse, m_specular, m_shininess;
};

#endif //MATERIAL_H

#include "sphere.h"

bool Sphere::operator==(const Sphere& other) const {
	// Check if origins are equal within a tolerance
	return glm::distance(m_origin, other.getOrigin()) < 1e-6 && std::abs(m_radius - other.getRadius()) < 1e-6;
}

glm::dvec4 Sphere::getOrigin() const
{
	return m_origin;
}
double Sphere::getRadius() const
{
	return m_radius;
}
glm::dmat4 Sphere::getTransform() const
{
	return m_transform;
}
void Sphere::setTransform(glm::dmat4 transformation)
{
	m_transform = transformation;
}




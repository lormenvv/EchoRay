#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class Ray {
public:
	Ray(glm::dvec3 origin, glm::dvec3 direction) {
		m_origin = glm::dvec4(origin, 1.0);
		m_direction = glm::dvec4(direction, 0.0);
	}
	glm::dvec4 position(double t) const {
		return m_origin + m_direction * t;
	}
	glm::dvec4 getOrigin() const {
		return m_origin;
	}
	glm::dvec4 getDirection() const {
		return m_direction;
	}
	Ray transform(glm::dmat4 transformation)
	{
		return Ray(transformation * m_origin, transformation * m_direction);
	}
private:
	glm::dvec4 m_origin, m_direction;
};

#endif
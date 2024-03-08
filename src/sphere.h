#ifndef SPHERE_H
#define SPHERE_H

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>


static int id = 0;

class Sphere {
public:
	Sphere() {
		m_origin = glm::dvec4(0, 0, 0, 1);
		m_radius = 1.0;
		m_transform = glm::dmat4(1.0);
		id++;
	}
	bool operator==(const Sphere& other) const;
	glm::dvec4 getOrigin() const;
	double getRadius() const;
	glm::dmat4 getTransform() const;
	void setTransform(glm::dmat4 transformation);
private:
	glm::dvec4 m_origin;
	double m_radius;
	glm::dmat4 m_transform;
};



#endif
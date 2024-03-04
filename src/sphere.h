#ifndef SPHERE_H
#define SPHERE_H

#include <glm/vec4.hpp>
#include "glm/geometric.hpp"


static int id = 0;

class Sphere {
public:
	Sphere() {
		m_origin = glm::dvec4(0, 0, 0, 1);
		m_radius = 1.0;
		id++;
	}
	bool operator==(const Sphere& other) const;
	glm::dvec4 getOrigin() const;
	double getRadius() const;
private:
	glm::dvec4 m_origin;
	double m_radius;
};



#endif
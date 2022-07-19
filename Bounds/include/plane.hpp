#pragma once

#include <glm/glm.hpp>
#include "bounds.hpp"
#include "aabb.hpp"

class Plane : public Bounds {
private:
	glm::vec3 normal;
	float distance;

public:
	Plane(float a, float b, float c, float d) {
		normal = glm::normalize(glm::vec3(a, b, c));
		distance = d;
	}

	glm::vec3 getNormal() const { return normal; }
	float getDistance() const { return distance; }
	float getDistanceFromPlane(const glm::vec3& point) const { return glm::dot(normal, point) - distance; }

	virtual bool intersects(const Bounds* o) const override;
	virtual bool contains(const glm::vec3& point) const override { return getDistanceFromPlane(point) == 0; }
	virtual glm::vec3 getCenter() const override {
		throw std::string("Unsupported Plane operaton");
	}
};
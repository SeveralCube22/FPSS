#pragma once

#include <glm/glm.hpp>
#include <string>
#include "bounds.hpp"

class AABB : public Bounds {
private:
	glm::vec3 center;
	float size;
	glm::vec3 extents;
	glm::vec3 min;
	glm::vec3 max;

public:
	AABB() {}
	AABB(glm::vec3 center, float size) : center(center), size(size) {
		float half = size / 2;
		extents = glm::vec3(half, half, half);
		min = center - extents;
		max = center + extents;
	}

	glm::vec3 getCenter() const { return center; }
	glm::vec3 getExtents() const { return extents; }
	glm::vec3 getMin() const { return min; }
	glm::vec3 getMax() const { return max; }
	float getSize() const { return size; }

	virtual bool intersects(const Bounds* o) const override;
	virtual bool contains(const glm::vec3& point) const override;
};
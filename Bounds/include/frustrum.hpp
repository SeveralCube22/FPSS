#pragma once

#include <vector>
#include "bounds.hpp"
#include "plane.hpp"

class Frustrum : public Bounds {
private:
	std::vector<Plane> planes; // ORGANIZED BY LEFT, RIGHT, DOWN, UP, NEAR, far. change to hashmap in the future
	Plane createPlane(const glm::vec4& m1, const glm::vec4& m2, bool add);

public:
	Frustrum(const glm::mat4x4& pv);
	
	virtual bool intersects(const Bounds* o) const override;
	virtual bool contains(const glm::vec3& point) const;
	virtual glm::vec3 getCenter() const override {
		throw std::string("Unsupported Frustrum operaton");
	}

	std::vector<Plane> getPlanes() const { return planes; }
};
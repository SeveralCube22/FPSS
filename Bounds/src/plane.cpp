#pragma once

#include "plane.hpp"
#include "bounds_helpers.hpp"

bool Plane::intersects(const Bounds* o) const {
	std::string type = Bounds::getType(o);
	if (type == "class AABB")
		return aabbIntersectsPlane(*(dynamic_cast<const AABB*>(o)), *this);
	throw std::string("Unsupported encapsulation");
}
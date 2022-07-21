#include "aabb.hpp"
#include "frustum.hpp"
#include "bounds_helpers.hpp"

bool AABB::intersects(const Bounds* o) const {
	std::string type = Bounds::getType(o);
	if (type == "class AABB")
		return aabbIntersectsAABB(*this, *(dynamic_cast<const AABB*>(o)));
	else if (type == "class Frustum")
		return aabbIntersectsFrustum(*this, *(dynamic_cast<const Frustum*>(o)));
	throw std::string("Unsupported encapsulation");
}

bool AABB::contains(const glm::vec3& point) const {
	return point.x >= min.x && point.y >= min.y && point.z >= min.z &&
		point.x <= max.x && point.y <= max.y && point.z <= max.z;
}
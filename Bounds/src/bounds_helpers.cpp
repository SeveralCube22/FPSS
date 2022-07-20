#include "bounds_helpers.hpp"

bool aabbIntersectsAABB(const AABB& o1, const AABB& o2) {
	return o1.contains(o2.getMin()) && o1.contains(o2.getMax());
}

bool aabbIntersectsPlane(const AABB& o1, const Plane& o2) {
	const glm::vec3& extents = o1.getExtents();
	float r = extents.x * std::abs(o2.getNormal().x) + extents.y * std::abs(o2.getNormal().y) + extents.z * std::abs(o2.getNormal().z);
	
	return std::abs(o2.getDistanceFromPlane(o1.getCenter())) <= r;
}

bool aabbIntersectsFrustrum(const AABB& o1, const Frustrum& o2) {
	for (const Plane& plane : o2.getPlanes())
		if (aabbIntersectsPlane(o1, plane))
			return true;
	return false;
}
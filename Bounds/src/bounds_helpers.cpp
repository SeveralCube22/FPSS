#include "bounds_helpers.hpp"

bool aabbIntersectsAABB(const AABB& o1, const AABB& o2) {
	return o1.contains(o2.getMin()) && o1.contains(o2.getMax());
}

bool aabbIntersectsFrustum(const AABB& o1, const Frustum& o2) {
	return o2.IsBoxVisible(o1.getMin(), o1.getMax());
}
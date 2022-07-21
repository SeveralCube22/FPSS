#pragma once

#include "aabb.hpp"
#include "frustum.hpp"
#include "plane.hpp"

bool aabbIntersectsAABB(const AABB& o1, const AABB& o2);
bool aabbIntersectsPlane(const AABB& o1, const Plane& o2);
bool aabbIntersectsFrustum(const AABB& o1, const Frustum& o2);
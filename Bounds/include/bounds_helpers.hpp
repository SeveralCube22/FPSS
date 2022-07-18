#pragma once

#include "aabb.hpp"
#include "frustrum.hpp"
#include "plane.hpp"

bool aabbIntersectsAABB(const AABB& o1, const AABB& o2);
bool aabbIntersectsPlane(const AABB& o1, const Plane& o2);
bool aabbIntersectsFrustrum(const AABB& o1, const Frustrum& o2);
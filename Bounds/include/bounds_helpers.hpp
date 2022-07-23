#pragma once

#include "aabb.hpp"
#include "frustum.hpp"

bool aabbIntersectsAABB(const AABB& o1, const AABB& o2);
bool aabbIntersectsFrustum(const AABB& o1, const Frustum& o2);
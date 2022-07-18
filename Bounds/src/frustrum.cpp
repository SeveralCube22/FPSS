#include "frustrum.hpp"
#include "bounds_helpers.hpp"

Frustrum::Frustrum(const glm::mat4x4& pv) {
	planes.push_back(createPlane(pv[3], pv[0], true)); // left
	planes.push_back(createPlane(pv[3], pv[0], false)); // right
	planes.push_back(createPlane(pv[3], pv[1], true)); // down
	planes.push_back(createPlane(pv[3], pv[1], false)); // up
	planes.push_back(createPlane(pv[3], pv[2], true)); // near
	planes.push_back(createPlane(pv[3], pv[2], false)); // far
}

bool Frustrum::contains(const glm::vec3& point) const {
	float left = planes[0].getDistanceFromPlane(point);
	float right = planes[1].getDistanceFromPlane(point);
	float down = planes[2].getDistanceFromPlane(point);
	float up = planes[3].getDistanceFromPlane(point);
	float near = planes[4].getDistanceFromPlane(point);
	float far = planes[5].getDistanceFromPlane(point);

	return left > 0 && right < 0 && up < 0 && down > 0 && near > 0 && far < 0;
}

Plane Frustrum::createPlane(const glm::vec4& m1, const glm::vec4& m2, bool add) {
	float sign = add ? 1 : -1;
	glm::vec4 res = m1 + sign * m2;
	return Plane(res[0], res[1], res[2], res[3]);
}

bool Frustrum::intersects(const Bounds* o) const {
	std::string type = Bounds::getType(o);
	if (type == "AABB")
		return aabbIntersectsFrustrum(*(dynamic_cast<const AABB*>(o)), *this);
	throw std::string("Unsupported encapsulation");
}
#pragma once

#include <glm/glm.hpp>
#include <set>
#include "edge.hpp"

enum EventType {
	UPPER,
	LOWER,
	INTERSECTION
};

class Event {
private:
	const glm::vec3& point;
	EventType type;
	std::set<Edge> upper;
	std::set<Edge> lower;
	std::set<Edge> interior;

public:
	Event(const glm::vec3& point, EventType type, std::set<Edge>& upper, std::set<Edge>& lower, std::set<Edge>& interior) 
		: point(point), type(type), upper(upper), lower(lower), interior(interior)
	{}

	glm::vec3 getPoint() const { return this->point; }

	std::set<Edge>& getUpper() { return upper; }
	std::set<Edge>& getLower() { return lower; }
	std::set<Edge>& getInterior() { return interior; }

	friend bool operator<(const Event& e1, const Event& e2);
	friend bool operator>(const Event& e1, const Event& e2);
};

bool operator<(const Event& e1, const Event& e2) {
	if (e1.point.y == e2.point.y)
		return e1.point.x < e2.point.x;
	return e1.point.y < e2.point.y;
}

bool operator>(const Event& e1, const Event& e2) {
	return !(e1 < e2);
}
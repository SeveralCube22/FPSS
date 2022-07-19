#pragma once

#include <glm/glm.hpp>
#include <typeinfo>
#include <string>

class Bounds {
public:
	virtual bool intersects(const Bounds* o) const = 0;
	virtual bool contains(const glm::vec3& point) const = 0;
	virtual glm::vec3 getCenter() const = 0;
	std::string getType(const Bounds* o) const { return std::string(typeid(*o).name()); }
};
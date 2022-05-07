#pragma once

#include <map>
#include <queue>
#include "event.hpp"
#include "edge.hpp"

namespace Utility {

	namespace {
		void handleEvent(std::priority_queue<Event>& Q, std::map<Edge, int, std::less<>>& status, std::map<glm::vec3, std::set<Edge>>, Event e);
	}

	std::map<glm::vec3, std::set<Edge>> computeIntersections(const std::vector<Edge>& edges);
}
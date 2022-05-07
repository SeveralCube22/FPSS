#pragma once

namespace Utility {

	namespace {
		void handleEvent(std::priority_queue<Event>& Q, std::map<Edge, int, std::less<>>& status, std::map<glm::vec3, std::set<Edge>>, Event e);
	}

	std::map<glm::vec3, std::set<Edge>> computeIntersections(const std::vector<Edge>& edges);
}
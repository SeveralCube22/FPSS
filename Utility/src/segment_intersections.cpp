
#include <vector>
#include <algorithm>
#include "utility.hpp"

namespace Utility {

	namespace {
		void handleEvent(std::priority_queue<Event>& Q, std::map<Edge, int, std::less<>>& status, std::map<glm::vec3, std::set<Edge>>, Event e) {
			std::set<Edge> upper = e.getUpper();
			glm::vec3 point = e.getPoint();

			std::set<Edge> containedP;
			while (status.find(point) != status.end()) { // deleting edges with lower endpoints == p and edges where p is on
				auto it = status.find(point); 
				containedP.insert(it->first);
				status.erase(it);
			}

			// handle intersections

			std::set<Edge> interior;
			for (Edge e : containedP)
				if (e.getLower() != point)
					interior.insert(e);
			
			*Edge::currSweepLine = (e.getPoint().y + Q.top().getPoint().y) / 2; // insert new segments based on new sweep line
			for (Edge e : upper)
				status.emplace(e, 0);
			for (Edge e : interior)
				status.emplace(e, 0);

			if (upper.size() == 0 && interior.size() == 0) {

			}
			else {

			}
		}
	}

	std::map<glm::vec3, std::set<Edge>> computeIntersections(const std::vector<Edge>& edges) {
		std::map<glm::vec3, std::set<Edge>> intersections;

		std::map<Edge, int, std::less<>> status;

		std::priority_queue<Event> Q;
		for (const Edge& e : edges) {
			std::set<Edge> u, l, c;
			u.insert(e);
			Q.push(Event(e.getUpper(), EventType::UPPER, u, l, c));
		}
		float* currSweepLine = new float();
		Edge::currSweepLine = currSweepLine;

		while (!Q.empty()) {
			Event e = Q.top();
			Q.pop();
			*currSweepLine = e.getPoint().y;
			handleEvent(Q, status, intersections, e);
		}

		return intersections;
	}
}
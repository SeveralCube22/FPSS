#include "utility.hpp"
#include <vector>
#include "vertex.hpp"
#include "edge.hpp"

int main() {
	Vertex v1 = { glm::vec3(1, 2, 0), glm::vec3(), glm::vec3() };
	Vertex v2 = { glm::vec3(3, -5, 0), glm::vec3(), glm::vec3() };
	
	Vertex v3 = { glm::vec3(4, -1, 0), glm::vec3(), glm::vec3() };
	Vertex v4 = { glm::vec3(2, -6, 0), glm::vec3(), glm::vec3() };

	Vertex v5 = { glm::vec3(6, 5, 0), glm::vec3(), glm::vec3() };
	Vertex v6 = { glm::vec3(9, -6, 0), glm::vec3(), glm::vec3() };

	Vertex v7 = { glm::vec3(9, -3, 0), glm::vec3(), glm::vec3() };
	Vertex v8 = { glm::vec3(4, -5, 0), glm::vec3(), glm::vec3() };

	Edge e1(&v1, &v2);
	Edge e2(&v3, &v4);
	Edge e3(&v5, &v6);
	Edge e4(&v7, &v8);

	std::vector<Edge> edges;
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	edges.push_back(e4);

	auto res = Utility::computeIntersections(edges);
}
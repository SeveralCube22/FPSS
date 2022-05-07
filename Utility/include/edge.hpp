#pragma once

#include <string>
#include "vertex.hpp"

class Edge {
private:
	Vertex* upper;
	Vertex* lower;

public:
	static float* currSweepLine;
	
	Edge(Vertex* upper, Vertex* lower) : upper(upper), lower(lower)
	{}

	const glm::vec3& getUpper() const { upper->pos; }
	const glm::vec3& getLower() const { lower->pos; }
	
	float getScalar() const {
		if (currSweepLine == nullptr)
			throw std::string("CURRENT SWEEP LINE IS NOT SET FOR EDGES");
		return (*currSweepLine - this->getUpper().y) / (this->getLower().y - this->getUpper().y);
	}

	friend bool operator<(const Edge& e1, const Edge& e2);
	friend bool operator<(const Edge& e1, const glm::vec3& p);
	friend bool operator<(const glm::vec3& p, const Edge& e1);

};

bool operator<(const Edge& e1, const Edge& e2) {
	float u1 = e1.getScalar();
	float u2 = e2.getScalar();

	float x1 = e1.getUpper().x + (e1.getLower().x - e1.getUpper().x) * u1;
	float x2 = e2.getUpper().x + (e2.getLower().x - e2.getUpper().x) * u2;
	return x1 < x2;
}

bool operator<(const Edge& e1, const glm::vec3& p) {
	float yScalar = (p.y - e1.getUpper().y) / (e1.getLower().y - e1.getUpper().y);
	float xScalar = (p.x - e1.getUpper().x) / (e1.getLower().x - e1.getUpper().x);

	if (yScalar == xScalar) return false;
	else {
		float x = e1.getUpper().x + (e1.getLower().x - e1.getUpper().x) * e1.getScalar();
		return x < p.x;
	}
}

bool operator<(const glm::vec3& p, const Edge& e1) {
	float yScalar = (p.y - e1.getUpper().y) / (e1.getLower().y - e1.getUpper().y);
	float xScalar = (p.x - e1.getUpper().x) / (e1.getLower().x - e1.getUpper().x);

	if (yScalar == xScalar) return false;
	else {
		float x = e1.getUpper().x + (e1.getLower().x - e1.getUpper().x) * e1.getScalar();
		return p.x < x;
	}
}

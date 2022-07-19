#pragma once

#include <vector>
#include "aabb.hpp"
#include "scene_node_interface.hpp"

class Octree {
private:
	enum Region {
		BottomLeftBack = 000,
		BottomLeftFront = 001,
		BottomRightBack = 010,
		BottomRightFront = 011,
		TopLeftBack = 100,
		TopLeftFront = 101,
		TopRightBack = 110,
		TopRightFront = 111,
	};
	struct Node {
		std::vector<ISceneNode*>* data;
		AABB bounds;
		std::vector<Node*>* children;
	};
	Node* root;
	int minSize;
	int maxObjects;
	float looseness;

	bool insertHelper(Node* node, ISceneNode* obj);
	Region findOctant(Node* node, const Bounds* bounds);
	void split(Node* node);

public:
	Octree(AABB bounds, int minSize, int maxObjects, float loosness);
	bool insert(ISceneNode* data);
	Node* getRoot() { return root; }

	friend class OctreeNode;
};
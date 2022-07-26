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

		~Node() {
			delete data;
			if (children != nullptr) {
				for (Node* node : *children)
					delete node;
			}
			delete children;
		}
	};
	Node* root;
	int minSize;
	int maxObjects;
	float looseness;

	bool insertHelper(Node* node, ISceneNode* obj);
	Region findOctant(Node* node, glm::vec3 o);
	void split(Node* node);
	ISceneNode* getDataHelper(Node* node, glm::vec3 o);
	ISceneNode* checkNodeData(Node* node, glm::vec3 o);

public:
	Octree(AABB bounds, int minSize, int maxObjects, float loosness);
	bool insert(ISceneNode* data);
	Node* getRoot() { return root; }
	ISceneNode* getData(glm::vec3 point);

	~Octree() {
		delete root;
	}

	friend class OctreeNode;
};
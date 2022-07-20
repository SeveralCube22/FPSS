#include "octree.hpp"
#include "scene_node_properties.hpp"

Octree::Octree(AABB bounds, int minSize, int maxObjects, float looseness) : minSize(minSize), maxObjects(maxObjects), looseness(looseness) {
	root = new Node();
	root->bounds = AABB(bounds.getCenter(), looseness * bounds.getSize());
}

bool Octree::insert(ISceneNode* data) {
	if (root->bounds.intersects(data->getProperties()->getBounds())) { // unnecessary check since box of the root will cover the entire scene
		return insertHelper(root, data);
	}
	return false;
}

bool Octree::insertHelper(Node* node, ISceneNode* obj) {
	if (node->children == nullptr) {
		if (node->data == nullptr || node->data->size() < maxObjects || ((node->bounds.getExtents() * .5f).x) < minSize) // comparing minSize to size of box, since size of box is vec using just x. Note could use y or z doesn't matter.
		{
			node->data = node->data ? node->data : new std::vector<ISceneNode*>();
			node->data->push_back(obj);
			return true;
		}
		else { // have to subdivide this node since it contains the max number of data objects
			split(node);
			for (int i = 0; i < node->data->size(); i++) {  // move objects currently in this node to see if they fit in child nodes
				ISceneNode* cObj = node->data->at(i);
				int bestChild = findOctant(node, cObj->getProperties()->getBounds());
				Node* child = node->children->at(bestChild);
				if (child->bounds.intersects(cObj->getProperties()->getBounds())) {
					insertHelper(child, cObj);
					node->data->erase(node->data->begin() + i);
				}
			}
		}
	}

	int bestChild = findOctant(node, obj->getProperties()->getBounds());
	Node* child = node->children->at(bestChild);
	if (child->bounds.intersects(obj->getProperties()->getBounds()))
		return insertHelper(child, obj);
	else {
		node->data->push_back(obj);
		return true;
	}
}

Octree::Region Octree::findOctant(Node* node, const Bounds* bounds) {
	glm::vec3 n = node->bounds.getCenter();
	glm::vec3 o = bounds->getCenter();
	int index = 0;
	index += o.z <= n.z ? 0 : 1;
	index += o.x <= n.x ? 0 : 2;
	index += o.y <= n.y ? 0 : 4;

	return static_cast<Region>(index);
}

void Octree::split(Node* node) {
	node->children = new std::vector<Node*>(); 
	glm::vec3 center = node->bounds.getCenter();
	glm::vec3 newCenterExtents = node->bounds.getExtents() * .5f;

	float size = looseness * node->bounds.getSize() / 2; 

	for (int i = 0; i < 8; i++) { // 8 children because octree. each node will have 8 children representing the 8 diff octants
		Node* c = new Node();
		glm::vec3 direction;

		int value = static_cast<Region>(i);
		direction.z = value & 1 ? 1 : -1; // mask is 001
		direction.x = value & 2 ? 1 : -1; // mask is 010
		direction.y = value & 4 ? 1 : -1; //mask is 100

		glm::vec3 nCenter = center + direction * newCenterExtents;

		c->bounds = AABB(nCenter, size);
		node->children->push_back(c);
	}
}
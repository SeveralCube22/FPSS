#include <map>
#include <vector>
#include <typeinfo>
#include "model_node.hpp"
#include "instance_node.hpp"
#include "octree_node.hpp"
#include "aabb.hpp"
#include "scene.hpp"


bool OctreeNode::addChild(ISceneNode* node) {
	SceneNode::addChild(node);
	return Scene::getInstance()->getOctree()->insert(node);
}

void OctreeNode::renderChildren() {
	Scene* scene = Scene::getInstance();
	Frustum view = scene->getViewBounds();
	std::map<std::string, std::vector<ModelNode*>> visible;
	renderChildrenHelper(scene->getOctree()->getRoot(), view, visible);
	
	for (auto iter = visible.begin(); iter != visible.end(); iter++) {
		std::vector<ModelNode*> nodes = iter->second;
		std::vector<glm::mat4x4> transforms;
		for (ModelNode* node : nodes)
			transforms.push_back(node->getProperties()->getTransform());
		
		InstanceNode instanced(nodes[0]->getObjPath(), nodes[0]->getShaders(), transforms);
		// load any necessary models depending on player location. maybe scene should be responsible for loading and unloading
		instanced.preRender();
		instanced.render();
		instanced.postRender();
		// unload any unnecessary models depending on player location
	}
}

void OctreeNode::renderChildrenHelper(Octree::Node* node, const Frustum& view, std::map<std::string, std::vector<ModelNode*>>& visible) {
	if (node->bounds.intersects(&view)) {
		if (node->data) // render all the objects that this node has
			for (int i = 0; i < node->data->size(); i++) {
				ISceneNode* data = node->data->at(i);
				if (data->getProperties()->getBounds()->intersects(&view)) {
					std::string name = data->getProperties()->getName();
					if (visible.find(name) == visible.end()) {
						std::vector<ModelNode*> nodes;
						nodes.push_back(dynamic_cast<ModelNode*>(data));
						visible.emplace(name, nodes);
					}
					else
						visible[name].push_back(dynamic_cast<ModelNode*>(data));
				}
			}

		// check which octant cubes are being intersected with view Frustum and render those cubes. 
		if (node->children)
			for (int i = 0; i < node->children->size(); i++)
				renderChildrenHelper(node->children->at(i), view, visible);
	}
}
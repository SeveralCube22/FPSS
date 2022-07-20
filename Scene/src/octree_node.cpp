#include <map>
#include <vector>
#include <typeinfo>

#include "octree_node.hpp"
#include "aabb.hpp"
#include "scene.hpp"

static int count = 0;

bool OctreeNode::addChild(ISceneNode* node) {
	SceneNode::addChild(node);
	return Scene::getInstance()->getOctree()->insert(node);
}

void OctreeNode::renderChildren() {
	Scene* scene = Scene::getInstance();
	Frustrum view = scene->getViewBounds();
	//std::map<std::string, std::vector<ModelNode*>> visible;
	std::cout << "Rendered: ";
	renderChildrenHelper(scene->getOctree()->getRoot(), view);
	std::cout << count << " objects" << std::endl;
	count = 0;
	//for (auto iter = visible.begin(); iter != visible.end(); iter++) {
	//	InstanceNode instanced(iter->second);
	//	// load any necessary models depending on player location. maybe scene should be responsible for loading and unloading
	//	instanced.preRender();
	//	instanced.render();
	//	instanced.postRender();
	//	// unload any unnecessary models depending on player location
	//}
}

void OctreeNode::renderChildrenHelper(Octree::Node* node, const Frustrum& view) {
	if (node->bounds.intersects(&view)) {
		if (node->data) // render all the objects that this node has
			for (int i = 0; i < node->data->size(); i++) {
				ISceneNode* data = node->data->at(i);
				/*std::string name = data->getProperties()->getName();
				if (visible.find(name) == visible.end()) {
					std::vector<ModelNode*> nodes;
					nodes.push_back(dynamic_cast<ModelNode*>(data));
					visible.emplace(name, nodes);
				}
				else
					visible[name].push_back(dynamic_cast<ModelNode*>(data));*/
				data->preRender();
				data->render();
				data->postRender();
				count++;
			}

		// check which octant cubes are being intersected with view frustrum and render those cubes. 
		if (node->children)
			for (int i = 0; i < node->children->size(); i++)
				renderChildrenHelper(node->children->at(i), view);
	}
}
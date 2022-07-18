#include "root_node.hpp"
#include <iostream>

RootNode::RootNode() : SceneNode(0, "Root", RenderPass_0, &(const glm::mat4x4&) glm::mat4x4(1.0f)) {
	glm::mat4x4 identity(1.0f);
	SceneNode* staticGroup = new SceneNode(UINT_MAX, "Static", RenderPass_Static, &identity);
	SceneNode* dynamicGroup = new SceneNode(UINT_MAX, "Dynamic", RenderPass_Dynamic, &identity);

	staticGroup->setParent(this);
	dynamicGroup->setParent(this);

	children.reserve(RenderPass_Last);
	children.push_back(staticGroup); // static group at pos RenderPass_Static
	children.push_back(dynamicGroup); // dynamic group at pos RenderPass_Dynamic
}

bool RootNode::addChild(ISceneNode* node) {
	RenderPass pass = node->getProperties()->getRenderPass();
	auto it = std::find_if(children.begin(), children.end(), [pass](ISceneNode* node) { return node->getProperties()->getRenderPass() == pass; });
	if (it != children.end())
		return (*it)->addChild(node);
	return false;
}

void RootNode::renderChildren() {
	for (int pass = RenderPass_0; pass < RenderPass_Last; pass++) {
		switch (pass) {
		case RenderPass_Static:
		case RenderPass_Dynamic:
			children[pass]->renderChildren();
			break;
		}
	}
}

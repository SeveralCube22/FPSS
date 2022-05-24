#include "root_node.hpp"

RootNode::RootNode() : SceneNode(0, "Root", RenderPass_0, &(const glm::mat4x4&) glm::mat4x4(1.0f), nullptr) {
	glm::mat4x4 identity(1.0f);
	SceneNode* staticGroup = new SceneNode(UINT_MAX, "Static", RenderPass_Static, &identity, this);
	SceneNode* dynamicGroup = new SceneNode(UINT_MAX, "Dynamic", RenderPass_Dynamic, &identity, this);


	children.reserve(RenderPass_Last);
	children[RenderPass_Static] = staticGroup;
	children[RenderPass_Dynamic] = dynamicGroup;
}

bool RootNode::addChild(ISceneNode* node) {
	RenderPass pass = node->getProperties()->getRenderPass();
	auto it = std::find_if(children.begin(), children.end(), [pass](ISceneNode* node) { return node->getProperties()->getRenderPass() == pass; });
	if (it != children.end())
		return (*it)->addChild(node);
	return false;
}

void RootNode::renderChildren(Scene& scene) {
	for (int pass = RenderPass_0; pass < RenderPass_Last; pass++) {
		switch (pass) {
		case RenderPass_Static:
		case RenderPass_Dynamic:
			children[pass]->renderChildren(scene);
			break;
		}
	}
}

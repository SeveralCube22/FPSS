#include "root_node.hpp"

RootNode::RootNode() : SceneNode(0, "Root", RenderPass_0, new glm::mat4x4(1.0f), nullptr) {
	SceneNode* staticGroup = new SceneNode(UINT_MAX, "Static", RenderPass_Static, new glm::mat4x4(1.0f), this);
	SceneNode* dynamicGroup = new SceneNode(UINT_MAX, "Dynamic", RenderPass_Dynamic, new glm::mat4x4(1.0f), this);


	children.insert(staticGroup);
	children.insert(dynamicGroup);
}
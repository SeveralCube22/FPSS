#include "scene_node.hpp"

void SceneNode::setTransform(const glm::mat4x4* to, const glm::mat4x4* from) {
	properties.toWorld = *to;
	if (from)
		properties.fromWorld = *from;
	else
		properties.fromWorld = glm::inverse(*to);
}

void SceneNode::onUpdate(const Scene& scene, float delta) {
	for (ISceneNode* child : children)
		child->onUpdate(scene, delta);
}

void SceneNode::onRestore(const Scene& scene) {
	for (ISceneNode* child : children)
		child->onRestore(scene);
}

void SceneNode::preRender(const Scene& scene) {
	scene.pushMatrix(properties.toWorld);
}

void SceneNode::postRender(const Scene& scene) {
	scene.popMatrix();
}

void SceneNode::renderChildren(const Scene& scene) {
	for (ISceneNode* child : children) {
		child->preRender(scene);
		child->render(scene);
		child->renderChildren(scene);
		child->postRender(scene);
	}
}

bool SceneNode::addChild(ISceneNode* node) {
	children.push_back(node);
	return true;
}

bool SceneNode::removeChild(int actorId) {

}
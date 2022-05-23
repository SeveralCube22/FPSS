#include "scene_node.hpp"
#include "scene.hpp"

void SceneNode::setTransform(const glm::mat4x4* to, const glm::mat4x4* from) {
	properties.toWorld = *to;
	if (from)
		properties.fromWorld = *from;
	else
		properties.fromWorld = glm::inverse(*to);
}

void SceneNode::onUpdate(Scene& scene, float delta) {
	for (ISceneNode* child : children)
		child->onUpdate(scene, delta);
}

void SceneNode::onRestore(const Scene& scene) {
	for (ISceneNode* child : children)
		child->onRestore(scene);
}

void SceneNode::preRender(Scene& scene) {
	scene.pushMatrix(properties.toWorld);
}

void SceneNode::postRender(Scene& scene) {
	scene.popMatrix();
}

void SceneNode::renderChildren(Scene& scene) {
	for (ISceneNode* child : children) {
		child->preRender(scene);
		if (child->isVisible(scene)) {
			child->render(scene);
			child->renderChildren(scene);
		}
		child->postRender(scene);
	}
}

bool SceneNode::addChild(ISceneNode* node) {
	auto res = children.emplace(node);
	return res.second;
}

bool SceneNode::removeChild(unsigned int actorId) { // possible O(log n) removal?
	for (ISceneNode* node : children) {
		if (node->getProperties()->actorId == actorId) {
			children.erase(node);
			return true;
		}
	}
	return false;
}

SceneNode::~SceneNode() {
	parent->removeChild(properties.actorId);
	for (ISceneNode* child : children)
		delete child;
}
#include "scene_node.hpp"
#include "scene.hpp"

void SceneNode::setTransform(const glm::mat4x4* to, const glm::mat4x4* from) {
	properties.toWorld = *to;
	if (from)
		properties.fromWorld = *from;
	else
		properties.fromWorld = glm::inverse(*to);
}

void SceneNode::setParent(ISceneNode* parent) {
	this->parent = parent;
}

void SceneNode::onUpdate(Scene& scene, float delta) {
	for (ISceneNode* child : children)
		child->onUpdate(scene, delta);
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
	if (std::find(children.begin(), children.end(), node) == children.end()) {
		node->setParent(this);
		children.push_back(node);
		return true;
	}
	return false;
}

bool SceneNode::removeChild(unsigned int actorId) {
	int index = -1;
	for (int i = 0; i < children.size(); i++) {
		if (children[i]->getProperties()->actorId == actorId) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		ISceneNode* child = children[index];
		children.erase(children.begin() + index);
		delete child;
		return true;
	}
	return false;
}

SceneNode::~SceneNode() {
	if (parent)
		parent->removeChild(properties.actorId);
	for (ISceneNode* child : children)
		delete child;
}
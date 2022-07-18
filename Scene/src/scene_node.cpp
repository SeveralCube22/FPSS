#include "scene_node.hpp"
#include "scene.hpp"

void SceneNode::setTransform(glm::mat4x4 to, const glm::mat4x4* from) {
	properties.toWorld = to;
	if (from)
		properties.fromWorld = *from;
	else
		properties.fromWorld = glm::inverse(to);
}

void SceneNode::setParent(ISceneNode* parent) {
	this->parent = parent;
}

void SceneNode::onUpdate(float delta) {
	for (ISceneNode* child : children)
		child->onUpdate(delta);
}

void SceneNode::preRender() {
	Scene::getInstance()->pushMatrix(properties.toWorld);
}

void SceneNode::postRender() {
	Scene::getInstance()->popMatrix();
}

void SceneNode::renderChildren() {
	for (ISceneNode* child : children) {
		child->preRender();
		if (child->isVisible()) {
			child->render();
			child->renderChildren();
		}
		child->postRender();
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
		return true;
	}
	return false;
}

SceneNode::~SceneNode() {
	for (ISceneNode* child : children)
		delete child;
	if (parent)
		parent->removeChild(properties.actorId);
}
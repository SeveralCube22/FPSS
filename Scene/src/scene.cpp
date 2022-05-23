#include "scene.hpp"


Scene::Scene(const std::string& scenePath) {

}

ISceneNode* Scene:: findActor(unsigned int actorId) {
	auto it = actors.find(actorId);
	return it == actors.end() ? nullptr : it->second;
}

bool Scene::addChild(unsigned int actorId, ISceneNode* node) {
	if (actors.find(actorId) == actors.end())
		actors.emplace(actorId, node);
	return root->addChild(node);
}

bool Scene::removeChild(unsigned int actorId) {
	actors.erase(actorId);
	return root->removeChild(actorId);
}

void Scene::onRender() {
	if (root) {
		root->preRender(*this);
		root->render(*this);
		root->postRender(*this);
	}
}

void Scene::onRestore() {
	if (root)
		root->onRestore(*this);
}

void Scene::onUpdate(float delta) {
	if (root) 
		root->onUpdate(*this, delta);
}

void Scene::pushMatrix(const glm::mat4x4& mat) {
	const glm::mat4x4& top = transformations.back();
	transformations.push_back(top * mat);
}

const glm::mat4x4& Scene::popMatrix() {
	const glm::mat4x4& top = transformations.back();
	transformations.pop_back();
	return top;
}

Scene::~Scene() {
	delete root;
 }
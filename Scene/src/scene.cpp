#include "scene.hpp"

Scene* Scene::scene;

Scene::Scene() {
	root = new RootNode();
}

Scene* Scene::getInstance() {
	if (!scene)
		scene = new Scene();
	return scene;
}

void Scene::destruct() {
	delete scene;
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
	auto it = actors.find(actorId);
	if (it != actors.end()) {
		it->second->getParent()->removeChild(actorId);
		actors.erase(actorId);
		delete it->second;
		return true;
	}
	return false;
}

void Scene::Render() {
	if (root) {
		root->preRender();
		root->renderChildren();
		root->postRender();
	}
}

void Scene::Update(float delta) {
	if (root) 
		root->onUpdate(delta);
}

void Scene::pushMatrix(const glm::mat4x4& mat) {
	if (transformations.empty())
		transformations.push_back(mat);
	else {
		const glm::mat4x4& top = transformations.back();
		transformations.push_back(top * mat);
	}
}

const glm::mat4x4& Scene::popMatrix() {
	if (transformations.empty())
		return glm::mat4x4(1.0f);

	const glm::mat4x4& top = transformations.back();
	transformations.pop_back();
	return top;
}

std::shared_ptr<Model> Scene::getModel(std::string objPath) {
	auto it = loadedModels.find(objPath);
	return it == loadedModels.end() ? nullptr : it->second;
}

Scene::~Scene() {
	delete root;
 }
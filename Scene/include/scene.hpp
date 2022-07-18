#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <model.hpp>
#include "root_node.hpp"

class Scene {
private:
	std::map<unsigned int, ISceneNode*> actors;
	std::map<std::string, std::shared_ptr<Model>> loadedModels;
	std::vector<glm::mat4x4> transformations;
	glm::mat4x4 PV;
	RootNode* root;

	static Scene* scene;
	Scene();

public:

	static Scene* getInstance();

	ISceneNode* findActor(unsigned int actorId);
	bool addChild(unsigned int actorId, ISceneNode* node);
	bool removeChild(unsigned int actorId);

	void Render();
	void Update(float delta);

	void setPVMatrix(const glm::mat4x4& pv) { this->PV = pv; }
	const glm::mat4x4& getPVMatrix() { return PV; }

	void pushMatrix(const glm::mat4x4& mat);
	const glm::mat4x4& popMatrix();

	void addModel(std::string objPath, std::shared_ptr<Model> m) { loadedModels.emplace(objPath, m); }
	std::shared_ptr<Model> getModel(std::string objPath);

	static void destruct();
	~Scene();
};
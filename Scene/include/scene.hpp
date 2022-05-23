#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "root_node.hpp"

class Scene {
private:
	std::map<unsigned int, ISceneNode*> actors;
	std::vector<glm::mat4x4> transformations;
	glm::mat4x4 PV;
	RootNode* root;

	void loadScene(const std::string& scenePath);

public:
	Scene(const std::string& scenePath);

	ISceneNode* findActor(unsigned int actorId);
	bool addChild(unsigned int actorId, ISceneNode* node);
	bool removeChild(unsigned int actorId);

	void onRender();
	void onRestore();
	void onUpdate(float delta);

	void setPVMatrix(const glm::mat4x4& pv) { this->PV = pv; }
	const glm::mat4x4& getPVMatrix() { return PV; }

	void pushMatrix(const glm::mat4x4& mat);
	const glm::mat4x4& popMatrix();

	~Scene();
};
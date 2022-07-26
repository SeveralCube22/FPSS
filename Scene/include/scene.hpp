#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <model.hpp>
#include "root_node.hpp"
#include "octree.hpp"
#include "frustum.hpp"

class Scene {
private:
	std::map<unsigned int, ISceneNode*> actors;
	std::map<std::string, std::shared_ptr<Model>> loadedModels;
	std::vector<glm::mat4x4> transformations;
	glm::mat4x4 PV;
	RootNode* root;
	Octree* tree;

	static Scene* scene;
	Scene();

public:

	static Scene* getInstance();
	
	void initOctree(AABB bounds, int minSize, int maxObjects, float looseness) {
		scene->tree = new Octree(bounds, minSize, maxObjects, looseness);
	}
	Octree* getOctree() { return tree; }
	ISceneNode* findActor(unsigned int actorId);
	bool addChild(unsigned int actorId, ISceneNode* node);
	bool removeChild(unsigned int actorId);

	void Render();
	void Update(float delta);

	void setPVMatrix(const glm::mat4x4& pv) { this->PV = pv; }
	const glm::mat4x4& getPVMatrix() { return PV; }
	Frustum getViewBounds() {
		return Frustum(this->getPVMatrix());
	}

	void pushMatrix(const glm::mat4x4& mat);
	const glm::mat4x4& popMatrix();

	void addModel(std::string objPath, std::shared_ptr<Model> m) { loadedModels.emplace(objPath, m); }
	std::shared_ptr<Model> getModel(std::string objPath);

	static void destruct();

	ISceneNode* getCollison(glm::vec3 point);

	~Scene();
};
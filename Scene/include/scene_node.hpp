#pragma once

#include <vector>
#include "scene_node_interface.hpp"
#include "scene_node_properties.hpp"

class SceneNode : public ISceneNode {
	friend class Scene;
private:
	ISceneNode* parent;
	std::vector<ISceneNode*> children;
	SceneNodeProperties properties;

public:
	SceneNode(int actorId, std::string name, RenderPass pass, const glm::mat4x4* to, const glm::mat4x4* from=nullptr) {
		parent = nullptr;
		properties.actorId = actorId;
		properties.name = name;
		this->setTransform(to, from);
	}

	virtual const SceneNodeProperties* const getProperties() const { return &properties; }
	virtual void setTransform(const glm::mat4x4* to, const glm::mat4x4* from);
	virtual void onUpdate(const Scene& scene, float delta);
	virtual void onRestore(const Scene& scene);

	virtual void preRender(const Scene& scene);
	virtual void isVisible(const Scene& scene) = 0;
	virtual void render(const Scene& scene);
	virtual void renderChildren(const Scene& scene);
	virtual void postRender(const Scene& scene);

	virtual bool addChild(ISceneNode* node);
	virtual bool removeChild(int actorId);

	glm::vec3 getPosition() { return glm::vec3(properties.toWorld[3]); }
	void setPosition(const glm::vec3& pos) { properties.toWorld[3] = glm::vec4(pos, 1.0f); }
	glm::vec3 getDirection(const glm::vec3& pos) { return this->getPosition() - pos; }

	// methods to set the bounding box or sphere for this node

	virtual ~SceneNode() {}
};
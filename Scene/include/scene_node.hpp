#pragma once

#include <vector>
#include "scene_node_interface.hpp"
#include "scene_node_properties.hpp"

class SceneNode : public ISceneNode {
	friend class Scene;
protected:
	ISceneNode* parent;
	std::vector<ISceneNode*> children;
	SceneNodeProperties properties;

public:
	SceneNode(unsigned int actorId, std::string name, RenderPass pass, const glm::mat4x4* to, const glm::mat4x4* from=nullptr) {
		parent = parent;
		properties.actorId = actorId;
		properties.name = name;
		properties.renderPass = pass;
		this->setTransform(to, from);
	}

	virtual const SceneNodeProperties* const getProperties() const override { return &properties; }
	virtual void setTransform(const glm::mat4x4* to, const glm::mat4x4* from) override;
	virtual glm::mat4x4& getTransform() override { return properties.toWorld; }

	virtual void setParent(ISceneNode* parent);

	virtual void onUpdate(float delta) override;

	virtual void preRender() override;
	virtual bool isVisible() const { return false; };
	virtual void render() override {} // for now do nothing for render. in the future, all scene nodes can have some sort of icons?
	virtual void renderChildren() override;
	virtual void postRender() override;

	virtual bool addChild(ISceneNode* node) override;
	virtual bool removeChild(unsigned int actorId) override;

	virtual ISceneNode* getParent() { return parent; }

	glm::vec3 getPosition() { return glm::vec3(properties.toWorld[3]); }
	void setPosition(const glm::vec3& pos) { properties.toWorld[3] = glm::vec4(pos, 1.0f); }
	glm::vec3 getDirection(const glm::vec3& pos) { return this->getPosition() - pos; }

	// methods to set the bounding box or sphere for this node

	virtual ~SceneNode();
};
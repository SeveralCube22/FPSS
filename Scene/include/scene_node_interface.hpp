#pragma once

#include <glm/glm.hpp>

class SceneNodeProperties;
class Scene;

class ISceneNode {
public:
	virtual const SceneNodeProperties* const getProperties() const = 0;
	virtual void setTransform(const glm::mat4x4* toWorld, const glm::mat4x4* fromWorld=nullptr) = 0; // sets this node's transform.
	
	virtual void onUpdate(Scene& scene, float delta) = 0; // things to do according to some delta time.

	virtual void preRender(Scene& scene) = 0; // any things to to do before rendering
	virtual bool isVisible(const Scene& scene) const = 0; // if this node is visible or not
	virtual void render(Scene& scene) = 0; // renders this node itself.
	virtual void renderChildren(Scene& scene) = 0; // renders this node's children
	virtual void postRender(Scene& scene) = 0; // any things to do after renderering

	virtual bool addChild(ISceneNode* node) = 0; // adds a child to the current node.
	virtual bool removeChild(unsigned int actorId) = 0; // this function is responsible for removing a child of the current node ONLY.

	virtual ISceneNode* getParent() = 0;

	virtual ~ISceneNode() {}
};
#pragma once

#include <glm/glm.hpp>

class SceneNodeProperties;
class Scene;

class ISceneNode {
public:
	virtual const SceneNodeProperties* const getProperties() const = 0;
	virtual void setTransform(const glm::mat4x4* toWorld, const glm::mat4x4* fromWorld=nullptr) = 0;
	virtual void onUpdate(Scene& scene, float delta) = 0;
	virtual void onRestore(const Scene& scene) = 0;

	virtual void preRender(Scene& scene) = 0;
	virtual bool isVisible(const Scene& scene) const = 0;
	virtual void render(const Scene& scene) = 0;
	virtual void renderChildren(Scene& scene) = 0;
	virtual void postRender(Scene& scene) = 0;

	virtual bool addChild(ISceneNode* node) = 0;
	virtual bool removeChild(unsigned int actorId) = 0;

	virtual ~ISceneNode() {}
};
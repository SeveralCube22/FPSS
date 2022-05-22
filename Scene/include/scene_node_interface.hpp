#pragma once

#include <glm/glm.hpp>

class SceneNodeProperties;
class Scene;

class ISceneNode {
public:
	virtual const SceneNodeProperties* const getProperties() const = 0;
	virtual void setTransform(const glm::mat4x4* toWorld, const glm::mat4x4* fromWorld=nullptr) const = 0;
	virtual void onUpdate(const Scene& scene, float delta) const = 0;
	virtual void onRestore(const Scene& scene) = 0;

	virtual void preRender(const Scene& scene) = 0;
	virtual bool isVisible(const Scene& scene) const = 0;
	virtual void render(const Scene& scene) = 0;
	virtual void renderChildren(const Scene& scene) = 0;
	virtual void postRender(const Scene& scene) = 0;

	virtual bool addChild(ISceneNode* node) = 0;
	virtual bool removeChild(int actorId) = 0;

	virtual ~ISceneNode() {}
};
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <bounds.hpp>

enum RenderPass {
	RenderPass_0, // starting pass
	RenderPass_Static = RenderPass_0,
	RenderPass_Dynamic,
	RenderPass_Sky,
	RenderPass_NotRendered, // objects that don't render but exist
	RenderPass_Last // counter for loops
};

class SceneNodeProperties {
	friend class SceneNode;

private:
	unsigned int actorId;
	std::string name;
	glm::mat4x4 toWorld, fromWorld;
	Bounds* bounds;

	RenderPass renderPass;

public:
	unsigned int getActorId() const { return actorId; }
	RenderPass getRenderPass() const { return renderPass; }
	const glm::mat4x4& getTransform() const { return toWorld; }
	const Bounds* getBounds() const { return bounds; }
	std::string getName() const { return name; }
	~SceneNodeProperties() {
		delete bounds;
	}
};
#pragma once

#include "scene_node.hpp"

class RootNode : public SceneNode {
public:
	RootNode();

	virtual bool addChild(ISceneNode* node) override;
	virtual void renderChildren(Scene& scene) override;
	virtual bool isVisible(const Scene& scene) const override { return true; }

	~RootNode();
};
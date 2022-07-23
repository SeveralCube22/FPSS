#pragma once

#include <vector>
#include <map>
#include "scene_node.hpp"
#include "model_node.hpp"
#include "frustum.hpp"
#include "octree.hpp"

class OctreeNode : public SceneNode {
private:
	void renderChildrenHelper(Octree::Node* node, const Frustum& view, std::map<std::string, std::vector<ModelNode*>>& visible);

public:
	OctreeNode(std::string name) : SceneNode(UINT_MAX, name, RenderPass_Static, new AABB(), glm::mat4x4(1.0f))
	{}

	virtual bool addChild(ISceneNode* node) override;
	//virtual bool removeChild(unsigned int actorId) override { return true; }

	virtual void renderChildren() override;
};
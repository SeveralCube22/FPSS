#pragma once

#include <string>
#include <map>
#include <vector>
#include <shader.hpp>
#include <buffer.hpp>
#include <aabb.hpp>
#include "scene_node.hpp"

class InstanceNode : public SceneNode {
private:
	std::string objPath;
	std::map<std::string, Shader> shaders;
	std::vector<glm::mat4x4> transforms;

public:
	InstanceNode(std::string objPath, const std::map<std::string, Shader>& shaders, const std::vector<glm::mat4x4>& transforms) 
		: SceneNode(UINT_MAX, "Instance Node", RenderPass_Static, new AABB(), glm::mat4x4(1.0f)), objPath(objPath), shaders(shaders), transforms(transforms)
	{}
	virtual void preRender() override;
	virtual void render() override;
};
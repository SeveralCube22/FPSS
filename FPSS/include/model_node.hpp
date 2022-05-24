#pragma once

#include <string>
#include <map>
#include <scene_node.hpp>
#include <shader.hpp>
#include <rapidjson/document.h>

class ModelNode : public SceneNode {
private:
	std::string objPath;
	std::map<std::string, Shader> shaders;
	
	static RenderPass getRenderPass(const std::string& pass);
	static std::map<std::string, Shader> getShaders(const rapidjson::Value& obj);
	static glm::mat4x4 getTransform(const rapidjson::Value& arr);
	
public:
	ModelNode(unsigned int actorId, std::string name, RenderPass pass, const glm::mat4x4& to, ISceneNode* parent,
		std::string objPath, const std::map<std::string, Shader> shaders) : SceneNode(actorId, name, pass, &to, parent),
		objPath(objPath), shaders(shaders) {}

	virtual void preRender(Scene& scene) override;
	virtual bool isVisible(const Scene& scene) const { return true; } // for now all meshes are visible
	virtual void render(Scene& scene) override;

	static ModelNode readJSON(const rapidjson::Value& object, ISceneNode* parent);
};
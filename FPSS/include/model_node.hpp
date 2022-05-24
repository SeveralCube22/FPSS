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
	Buffer modelBuffer;

	static RenderPass getRenderPass(const std::string& pass);
	static std::map<std::string, Shader> getShaders(const rapidjson::Value& obj);
	static glm::mat4x4 getTransform(const rapidjson::Value& arr);
	
public:
	ModelNode(unsigned int actorId, std::string name, RenderPass pass, const glm::mat4x4& to,
		std::string objPath, const std::map<std::string, Shader> shaders) : SceneNode(actorId, name, pass, &to),
		objPath(objPath), shaders(shaders), modelBuffer(GL_ARRAY_BUFFER) 
	{
		std::vector<glm::mat4x4> model = { properties.getTransform() };
		modelBuffer.addData(model.data(), 1 * sizeof(glm::mat4x4), GL_STATIC_DRAW);
	}

	virtual void preRender(Scene& scene) override;
	virtual bool isVisible(const Scene& scene) const { return true; } // for now all meshes are visible
	virtual void render(Scene& scene) override;

	static ModelNode* readJSON(const rapidjson::Value& object);
};
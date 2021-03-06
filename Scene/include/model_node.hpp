#pragma once

#include <string>
#include <map>
#include <scene_node.hpp>
#include <shader.hpp>
#include <rapidjson/document.h>
#include <bounds.hpp>

class ModelNode : public SceneNode {
private:
	std::string objPath;
	std::map<std::string, Shader> shaders;

	static RenderPass getRenderPass(const std::string& pass);
	static std::map<std::string, Shader> getShaders(const rapidjson::Value& obj);
	static glm::mat4x4 getTransform(const rapidjson::Value& arr);
	static glm::vec3 convertToVec(const rapidjson::Value& arr);
	
public:
	ModelNode(unsigned int actorId, std::string name, RenderPass pass, glm::mat4x4 to,
		std::string objPath, const std::map<std::string, Shader> shaders, Bounds* bounds) : SceneNode(actorId, name, pass, bounds, to),
		objPath(objPath), shaders(shaders)
	{
	}

	std::string getObjPath() const { return objPath; }
	const std::map<std::string, Shader>& getShaders() const { return shaders; }

	static ModelNode* readJSON(const rapidjson::Value& object);
};
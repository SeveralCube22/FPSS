#include "scene.hpp"
#include "model_node.hpp"
#include "model.hpp"
#include "mesh.hpp"
#include <glm\gtc\type_ptr.hpp>
#include <aabb.hpp>

ModelNode* ModelNode::readJSON(const rapidjson::Value& object) {
	unsigned int actorId = object["actorId"].GetUint();
	std::string name = object["name"].GetString();
	std::string objPath = object["objPath"].GetString();
	RenderPass renderPass = getRenderPass(object["renderPass"].GetString());
	std::map<std::string, Shader> shaders = getShaders(object["shaders"]);
	glm::mat4x4 to = getTransform(object["transform"]);

	/*
		TODO: For now assuming, all model nodes will have AABB. In the future, json file will generic bounds.
			  So in world.json, 
			  Bounds {
				type: Bound Type(AABB, Sphere, etc.)
				data: {
					data specific to bound type
				}
	*/
	const rapidjson::Value& aabbVal = object["aabb"];
	glm::vec3 center = convertToVec(aabbVal["center"]);
	float size = aabbVal["size"].GetFloat();

	return new ModelNode(actorId, name, renderPass, to, objPath, shaders, new AABB(center, size));
}

RenderPass ModelNode::getRenderPass(const std::string& pass) {
	if (pass == "STATIC")
		return RenderPass_Static;
	else if (pass == "DYNAMIC")
		return RenderPass_Dynamic;
	else
		throw std::string("INVALID RENDER PASS IN JSON");
}

std::map<std::string, Shader> ModelNode::getShaders(const rapidjson::Value& obj) {
	std::map<std::string, Shader> shaders;
	for (auto& m : obj.GetObject())
		shaders.emplace(m.name.GetString(), Shader(m.value.GetString()));
	return shaders;
}

glm::mat4x4 ModelNode::getTransform(const rapidjson::Value& arr) {
	std::vector<float> vals;
	for (auto& v : arr.GetArray())
		vals.push_back(v.GetFloat());
	return glm::make_mat4x4(&vals[0]);
}

glm::vec3 ModelNode::convertToVec(const rapidjson::Value& arr) {
	std::vector<float> vals;
	for (auto& v : arr.GetArray())
		vals.push_back(v.GetFloat());
	return glm::make_vec3(&vals[0]);
}
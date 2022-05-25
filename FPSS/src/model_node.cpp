#include "scene.hpp"
#include "model_node.hpp"
#include "model.hpp"
#include "mesh.hpp"
#include <glm\gtc\type_ptr.hpp>

void ModelNode::preRender(Scene& scene) {
	SceneNode::preRender(scene);

	std::shared_ptr<Model> m = scene.getModel(objPath);
	if (!m) {
		m = std::make_shared<Model>(objPath, shaders);
		scene.addModel(objPath, m);

		BufferLayout mLayout;

		for (int i = 0; i < 4; i++) // per instance vertex attrib layout
			mLayout.addElement(4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), sizeof(glm::vec4) * i, 1);

		for (Mesh mesh : m->getMeshes()) {
			VertexArray& vao = mesh.getVAO();
			vao.addBufferLayout({ modelBuffer }, { mLayout });
		}
	}
}

void ModelNode::render(Scene& scene) {
	std::shared_ptr<Model> model = scene.getModel(objPath);
	const glm::mat4x4& pv = scene.getPVMatrix();
	for (Mesh mesh : model->getMeshes()) {
		const Shader& shader = mesh.getShader();
		shader.bind();
		unsigned int pvId = shader.getUniformLocation("PV");
		glUniformMatrix4fv(pvId, 1, GL_FALSE, glm::value_ptr(pv[0]));

		mesh.setMesh(); // mesh will bind vertices, indices, and textures
		glDrawElementsInstanced(GL_TRIANGLES, mesh.getIndicesSize(), GL_UNSIGNED_INT, (void*)0, 1); // draw the only one model
		
		mesh.reset();
		shader.unbind();
	}
}

ModelNode* ModelNode::readJSON(const rapidjson::Value& object) {
	unsigned int actorId = object["actorId"].GetUint();
	std::string name = object["name"].GetString();
	std::string objPath = object["objPath"].GetString();
	RenderPass renderPass = getRenderPass(object["renderPass"].GetString());
	std::map<std::string, Shader> shaders = getShaders(object["shaders"]);
	glm::mat4x4 to = getTransform(object["transform"]);

	return new ModelNode(actorId, name, renderPass, to, objPath, shaders);
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
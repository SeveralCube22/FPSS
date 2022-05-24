#include "scene.hpp"
#include "model_node.hpp"
#include "model.hpp"
#include "mesh.hpp"
#include <glm\gtc\type_ptr.hpp>

void ModelNode::preRender(Scene& scene) {
	SceneNode::preRender(scene);

	std::shared_ptr<Model> m = scene.getModel(objPath);
	if (!m) 
		scene.loadModel(objPath, std::make_shared<Model>(objPath, shaders));
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
		glDrawElements(GL_TRIANGLES, mesh.getIndicesSize(), GL_UNSIGNED_INT, (void*)0);
		
		mesh.reset();
		shader.unbind();
	}
}
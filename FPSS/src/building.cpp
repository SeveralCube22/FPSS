#include "building.hpp"

void Building::setPVMatrix(const glm::mat4& pv) {
	for (Mesh mesh : Model::meshes) {
		const Shader& shader = mesh.getShader();
		shader.bind();
		unsigned int pvId = shader.getUniformLocation("PV");
		glUniformMatrix4fv(pvId, 1, GL_FALSE, glm::value_ptr(pv[0]));
		shader.unbind();
	}
}

void Building::draw() {
	for (Mesh mesh : Model::meshes) {
		const Shader& shader = mesh.getShader();
		shader.bind(); // mesh needs shader to bound for texture uniforms
		
		mesh.setMesh(); // mesh will bind vertices, indices, and textures
		
		glDrawElementsInstanced(GL_TRIANGLES, mesh.getIndicesSize(), GL_UNSIGNED_INT, (void*)0, models.size());
	
		mesh.reset(); // unbind vao's, textures, and indices
		shader.unbind();
	}
}

void Building::setupModelsBuf() {
	modelsBuf.addData(models.data(), models.size() * sizeof(glm::mat4), GL_STATIC_DRAW);
	BufferLayout mLayout;

	for (int i = 0; i < 4; i++) // per instance vertex attrib layout
		mLayout.addElement(4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), sizeof(glm::vec4) * i, 1);
	
	for (Mesh mesh : Model::meshes) {
		VertexArray& vao = mesh.getVAO();
		vao.addBufferLayout({ modelsBuf }, { mLayout });
	}
}
#include "mesh.hpp"


void Mesh::setupBuffers() {
	auto size = 2 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2);

	verticesBuf.addData<Vertex>(vertices.data(), vertices.size() * size, GL_STATIC_DRAW);
	indicesBuf.addData<unsigned int>(indices.data(), indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);
	
	BufferLayout verticesLayout;
	verticesLayout.addElement(3, GL_FLOAT, false, size, offsetof(Vertex, Vertex::pos), 0);
	verticesLayout.addElement(3, GL_FLOAT, false, size, offsetof(Vertex, Vertex::normal), 0);
	verticesLayout.addElement(2, GL_FLOAT, false, size, offsetof(Vertex, Vertex::texCoords), 0);

	vao.addBufferLayout({ verticesBuf }, { verticesLayout });
}

void Mesh::setMesh() {
	int diffuse = 1;
	int specular = 1;
	int normal = 1;

	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		TextureType type = textures[i].type;
		std::string uniformName;

		if (type == TextureType::DIFFUSE)
			uniformName = "tex_diffuse" + diffuse++;
		else if (type == TextureType::SPECULAR)
			uniformName = "tex_specular" + specular++;
		else
			uniformName = "tex_normal" + normal++;

		int uniformId = shader.getUniformLocation(uniformName);
		glUniform1i(uniformId, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	vao.bind();
	indicesBuf.bind();
}

void Mesh::reset() {
	vao.unbind();
	indicesBuf.unbind();
	glActiveTexture(GL_TEXTURE0);
}

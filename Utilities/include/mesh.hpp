#pragma once

#include <vector>
#include <string>
#include "vertex.hpp"
#include "texture.hpp"
#include "buffer.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"

// TODO: Maybe 1 vao for entire model instead 1 for each mesh?
class Mesh {
private:
	std::vector<Texture> textures;
	int indicesSize;

	Buffer verticesBuf;
	Buffer indicesBuf;
	VertexArray vao;
	Shader shader;

public:
	Mesh(const std::vector<Texture>& textures, const Shader& shader) : textures(textures), indicesSize(0),
																	   verticesBuf(GL_ARRAY_BUFFER), indicesBuf(GL_ELEMENT_ARRAY_BUFFER),
																       shader(shader)
	{
	}

	void setupBuffers(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	const Shader& getShader() const { return shader; }
	VertexArray& getVAO() { return vao; }
	void setMesh();
	void reset();
	int getIndicesSize() { return indicesSize; }
	
	void deleteBuffers() {
		verticesBuf.deleteBuffer();
		indicesBuf.deleteBuffer();
		vao.deleteVertexArray();
	}
};
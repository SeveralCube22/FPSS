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
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	 
	Buffer verticesBuf;
	Buffer indicesBuf;
	VertexArray vao;
	Shader shader;

	void setupBuffers();
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
		 const std::vector<Texture>& textures, const Shader& shader) : vertices(vertices), indices(indices), textures(textures),
																	   verticesBuf(GL_ARRAY_BUFFER), indicesBuf(GL_ELEMENT_ARRAY_BUFFER),
																       shader(shader)
	{
		this->setupBuffers();
	}

	const Shader& getShader() const { return shader; }
	VertexArray& getVAO() { return vao; }
	void setMesh();
	void reset();
	int getIndicesSize() { return indices.size(); }
};
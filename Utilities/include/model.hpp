#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "buffer.hpp"

class Model {
private:
	std::string dir;
	std::string objPath;

	std::map<std::string, Texture> textures_loaded;
	Buffer transformBuffer; // Model 

	void loadModel();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMatTextures(aiMaterial* mat, aiTextureType type, TextureType texType);
	unsigned int loadTexFromFile(const char* path, const std::string& directory, bool gamma);
	std::map<std::string, Shader> shaders;

protected:
	std::vector<Mesh> meshes;

public:
	Model(const std::string& objPath,
		const std::map<std::string, Shader>& shaders) : objPath(objPath), shaders(shaders), transformBuffer(GL_ARRAY_BUFFER)
	{
		dir = objPath.substr(0, objPath.find_last_of('/'));
		this->loadModel();

		BufferLayout mLayout; 

		for (int i = 0; i < 4; i++) // per instance vertex attrib layout
			mLayout.addElement(4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), sizeof(glm::vec4) * i, 1);

		for (Mesh& mesh : meshes) {
			VertexArray& vao = mesh.getVAO();
			vao.addBufferLayout({ transformBuffer }, { mLayout });
		}
	}
	std::vector<Mesh>& getMeshes() { return meshes; }
	void setTransforms(std::vector<glm::mat4x4>& transforms);
	void draw(const glm::mat4x4& pv);

	~Model() {
		for (Mesh& mesh : meshes)
			mesh.deleteBuffers();
	}
};
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

class Model {
private:
	std::string dir;
	std::string objPath;

	std::map<std::string, Texture> textures_loaded;

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
		const std::map<std::string, Shader>& shaders) : objPath(objPath), shaders(shaders)
	{
		dir = objPath.substr(0, objPath.find_last_of('/'));
		this->loadModel();
	}
	virtual void draw() = 0;
};
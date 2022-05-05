#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <cstddef>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "model.hpp"
#include "shader.hpp"


/* TODO:
*		- Building model has 3 meshes(main building, glass, paint)
		- Need shaders for each of these materials
		- Have to abstract further to account for each mesh having different shaders? (glass, paint don't have no 
																						tex coords so only 3 attribs (pos, normal, models)
*/
class Building : public Model {
private:
	Buffer modelsBuf;
public: 
	std::vector<glm::mat4> models;
	Building(const std::string& modelPath, const std::map<std::string, Shader>& shaders, const std::vector<glm::mat4>& models) : Model(modelPath, shaders), modelsBuf(GL_ARRAY_BUFFER), models(models)
	{
		this->setupModelsBuf();
	}
	// how to pass PV for draw
	// mesh will have vao for vertices and will take care of binding vertices and textures
	// specific models like building will take care of setting up transformation matrices PV and models and will have the ultimate draw call

	void setupModelsBuf();
	void setPVMatrix(const glm::mat4& pv);
	void draw();
};
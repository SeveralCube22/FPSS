#pragma once

#include "building.hpp"

class MassHall : public Building {
private:
	std::map<std::string, Shader> setupShaders() {
		std::map<std::string, Shader> shaders;
		std::string path = "res/shaders/";
		shaders.emplace("glass", Shader(path + "glass.glsl"));
		shaders.emplace("paint", Shader(path + "paint.glsl"));
		shaders.emplace("default", Shader(path + "building.glsl"));
		return shaders;
	};
public:
	MassHall(const std::string& modelPath, const std::vector<glm::mat4>& models) : Building(modelPath, setupShaders(), models)
	{}
};
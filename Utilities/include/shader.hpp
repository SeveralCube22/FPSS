#pragma once

#include <string>
#include <vector>

class Shader {
private:
	struct ShaderSource {
		std::string vertexSrc;
		std::string fragSrc;
	};

	std::string shaderFile;
	unsigned int programId;
	ShaderSource parseShaderFile(const std::string& file);
	unsigned int compileShader(const std::string& source, unsigned int type); // type = VERTEX or FRAGMENT
	unsigned int createShaderProgram(const ShaderSource& srcFiles);

public:
	Shader(const std::string& shaderFile);
	int getUniformLocation(const std::string& uniformName) const;
	int getProgramId() const { return programId; }
	void bind() const;
	void unbind() const;
};
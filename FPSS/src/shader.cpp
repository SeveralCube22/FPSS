#include "shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>


Shader::Shader(const std::string& shaderFile) : shaderFile(shaderFile) {
    ShaderSource src = this->parseShaderFile(shaderFile);
    this->programId = createShaderProgram(src);
}

unsigned int Shader::compileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr); // read docs
    glCompileShader(id);

    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* mssg = new char[len];
        glGetShaderInfoLog(id, len, &len, mssg);
        std::cout << "FAILED TO COMPILE: " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << std::endl;
        std::cout << mssg << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::createShaderProgram(const Shader::ShaderSource& srcFiles) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(srcFiles.vertexSrc, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(srcFiles.fragSrc, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

Shader::ShaderSource Shader::parseShaderFile(const std::string& file) {
    std::ifstream stream(file);
    enum class ShaderType {VERTEX, FRAGMENT, NONE}; // at the moment only supporting vertex and fragment.

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str()};
}

int Shader::getUniformLocation(const std::string& uniformName) const {
    return glGetUniformLocation(this->programId, uniformName.c_str());
}

void Shader::bind() const {
    glUseProgram(this->programId);
}

void Shader::unbind() const {
    glUseProgram(0);
}

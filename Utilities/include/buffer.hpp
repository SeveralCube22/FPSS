#pragma once

#include <glad\glad.h>
#include <stdio.h>

class Buffer {
private:
	unsigned int id;
	GLenum type;
	
public:
	Buffer(GLenum type) : type(type) {
		glGenBuffers(1, &id);
	}
	
	template<typename T>
	void addData(T* data, size_t size, GLenum usage);

	void bind() const { glBindBuffer(type, id); }
	void unbind() const { glBindBuffer(type, 0); }
	void unMapBuffer() const {
		this->bind();
		glUnmapBuffer(type);
		this->unbind();
	}

	template<typename T>
	T* mapBuffer(GLenum access);

	void deleteBuffer() {
		glDeleteBuffers(1, &id);
	}
};

template<typename T>
void Buffer::addData(T* data, size_t size, GLenum usage) {
	this->bind();
	glBufferData(type, size, nullptr, usage);
	
	T* bufferData = this->mapBuffer<T>(GL_WRITE_ONLY);
	memcpy(bufferData, data, size);
	
	this->unMapBuffer();
	this->unbind();
}

template<typename T>
T* Buffer::mapBuffer(GLenum access) {
	this->bind();
	void* data = glMapBuffer(type, access);
	this->unbind();
	return (T*)data;
}


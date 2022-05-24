#pragma once

#include <glad\glad.h>
#include <vector>
#include "buffer.hpp"
#include "buffer_layout.hpp"

class VertexArray {
private:
	unsigned int id;
	int currAttribLocation;
public:
	VertexArray() {
		currAttribLocation = 0;
		glGenVertexArrays(1, &id);
	}

	void addBufferLayout(const std::vector<Buffer>& buffers, const std::vector<BufferLayout>& layouts);
	
	void bind() const;
	void unbind() const;
};
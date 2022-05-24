#pragma once

#include <glad\glad.h>
#include <vector>

struct LayoutElement { // index of layout element is controlled by vertex array
	unsigned int size;
	GLenum type;
	bool normalized;
	unsigned int stride;
	void* pointer;
	int divisor; // for instance rendering
};

class BufferLayout {
private:
	std::vector<LayoutElement> elements;
public:
	void addElement(unsigned int size, GLenum type, bool normalized, unsigned int stride, unsigned int pointer, int divisior);
	std::vector<LayoutElement> getElements() const { return elements; }
};
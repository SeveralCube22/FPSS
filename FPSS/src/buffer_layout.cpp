#include "buffer_layout.hpp"

void BufferLayout::addElement(unsigned int size, GLenum type, bool normalized, unsigned int stride, unsigned int pointer, int divisior) {
	LayoutElement elem = { size, type, normalized, stride, (void*) pointer, divisior};
	elements.push_back(elem);
}
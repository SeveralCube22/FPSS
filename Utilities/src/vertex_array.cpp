#include "vertex_array.hpp"

#include <iostream>

void VertexArray::addBufferLayout(const std::vector< Buffer>& buffers, const std::vector<BufferLayout>& layouts) {
	this->bind();
	
	for (int i = 0; i < buffers.size(); i++) {
		buffers[i].bind();
		BufferLayout layout = layouts[i];
		std::vector<LayoutElement> elems = layout.getElements();
		
		for (int j = 0; j < elems.size(); j++, currAttribLocation++) { // for now, client has to order attributes accordingly. So pos has to be first, then color, etc.
			LayoutElement elem = elems[j];

			glEnableVertexAttribArray(currAttribLocation);
			glVertexAttribPointer(currAttribLocation, elem.size, elem.type, elem.normalized, elem.stride, elem.pointer);
			glVertexAttribDivisor(currAttribLocation, elem.divisor);
		}
		buffers[i].unbind();
	}

	this->unbind();
}

void VertexArray::bind() const {
	glBindVertexArray(this->id);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

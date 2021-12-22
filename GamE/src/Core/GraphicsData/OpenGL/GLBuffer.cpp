#include "pch.h"
#include "GLBuffer.h"

#include <glad/glad.h>

namespace GE {

	/* vertexbuf ************************************/

	GLVertexBuf::GLVertexBuf(float * vertices, uint32_t size)
	{
		glCreateBuffers(1, &_vertexBuf);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuf);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	GLVertexBuf::~GLVertexBuf()
	{
		glDeleteBuffers(1, &_vertexBuf);
	}
	void GLVertexBuf::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuf);
	}

	void GLVertexBuf::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/* indexbuf ************************************/

	GLIndexBuf::GLIndexBuf(uint32_t * vertices, uint32_t count) :_count(count)
	{
		glCreateBuffers(1, &_indexBuf);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuf);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(uint32_t), vertices, GL_STATIC_DRAW);
	}
	GLIndexBuf::~GLIndexBuf()
	{
		glDeleteBuffers(1, &_indexBuf);
	}
	void GLIndexBuf::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _indexBuf);
	}

	void GLIndexBuf::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}


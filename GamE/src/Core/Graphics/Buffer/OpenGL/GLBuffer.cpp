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

	/* vertexArr ************************************/
	/* > point to vertex & index, as a manager*******/

	static GLenum DataType_to_GLType(DataType type)
	{
		switch (type)
		{
		case GE::DataType::Float:
		case GE::DataType::Float2:
		case GE::DataType::Float3:
		case GE::DataType::Float4:
		case GE::DataType::Matrix3:
		case GE::DataType::Matrix4:
			return GL_FLOAT;
		case GE::DataType::Int:
		case GE::DataType::Int2:
		case GE::DataType::Int3:
		case GE::DataType::Int4:
			return GL_INT;
		case GE::DataType::Bool:
			return GL_BOOL;
		default:
			return 0;
		}
	}

	GLVertexArr::GLVertexArr()
	{
		glCreateVertexArrays(1, &_vertexArr);
	}
	void GLVertexArr::bind() const
	{
		glBindVertexArray(_vertexArr);
	}
	void GLVertexArr::unbind() const
	{
		glBindVertexArray(0);
	}
	void GLVertexArr::addVertex(const std::shared_ptr<VertexBuf>& vertexBuf)
	{
		glBindVertexArray(_vertexArr);
		vertexBuf->bind();

		COUT_ASSERT(vertexBuf->getLayout().get().size(), "[GLVertexArr] no BufLayout set");
		const auto& _layout = vertexBuf->getLayout();

		uint32_t ind = 0;
		for (const auto& buf : _layout)  // every row
		{
			glEnableVertexAttribArray(ind);
			glVertexAttribPointer(ind, buf.count(), DataType_to_GLType(buf.type), buf.isNorm, _layout.getStride(), (const void*)buf.offset);
			ind++;
		}

		_vertexBuf_vec.push_back(vertexBuf);
	}
	void GLVertexArr::setIndex(const std::shared_ptr<IndexBuf>& indexBuf)
	{
		glBindVertexArray(_vertexArr);
		indexBuf->bind();

		_indexBuf = indexBuf;
	}

}


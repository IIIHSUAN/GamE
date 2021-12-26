#include "pch.h"
#include "Buffer.h"

#include "../Renderer/Renderer.h"

#include "OpenGL/GLBuffer.h"

namespace GE {

	VertexBuf * VertexBuf::create(float * vertices, uint32_t count)
	{
		switch (RendererAPI::getType())
		{
		case RendererAPI::Type::None:
		default:
			COUT_ASSERT(0, "RendererAPI Type Not Found for VertexBuf");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return new GLVertexBuf(vertices, count);
		}
	}

	IndexBuf * IndexBuf::create(uint32_t * vertices, uint32_t count)
	{
		switch (RendererAPI::getType())
		{
		case RendererAPI::Type::None:
		default:
			COUT_ASSERT(0, "RendererAPI Type Not Found for IndexBuf");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return new GLIndexBuf(vertices, count);
		}
	}

	VertexArr * VertexArr::create()
	{
		switch (RendererAPI::getType())
		{
		case RendererAPI::Type::None:
		default:
			COUT_ASSERT(0, "RendererAPI Type Not Found for VertexBuf");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return new GLVertexArr();
		}
	}

	/* impl drawing ****************************************/


}

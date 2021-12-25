#include "pch.h"
#include "Buffer.h"

#include "../Renderer/Renderer.h"

#include "OpenGL/GLBuffer.h"

namespace GE {

	VertexBuf * VertexBuf::create(float * vertices, uint32_t count)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
		default:
			COUT_ASSERT(0, "RendererAPI NULL for VertexBuf");
			return nullptr;
		case RendererAPI::OpenGL:
			return new GLVertexBuf(vertices, count);
		}
	}

	IndexBuf * IndexBuf::create(uint32_t * vertices, uint32_t count)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
		default:
			COUT_ASSERT(0, "RendererAPI NULL for IndexBuf");
			return nullptr;
		case RendererAPI::OpenGL:
			return new GLIndexBuf(vertices, count);
		}
	}

	VertexArr * VertexArr::create()
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
		default:
			COUT_ASSERT(0, "RendererAPI NULL for VertexBuf");
			return nullptr;
		case RendererAPI::OpenGL:
			return new GLVertexArr();
		}
	}

	/* impl drawing ****************************************/


}

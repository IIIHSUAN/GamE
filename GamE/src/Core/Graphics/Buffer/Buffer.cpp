#include "pch.h"
#include "Buffer.h"

#include "../Renderer/Renderer.h"

#include "OpenGL/GLBuffer.h"

namespace GE {

	VertexBuf * VertexBuf::create(float * vertices, uint32_t count)
	{
		switch (RendererAPI::getName())
		{
		case RendererAPI::Name::None:
		default:
			COUT_ASSERT(0, "RendererAPI Name Not Found for VertexBuf");
			return nullptr;
		case RendererAPI::Name::OpenGL:
			return new GLVertexBuf(vertices, count);
		}
	}

	IndexBuf * IndexBuf::create(uint32_t * vertices, uint32_t count)
	{
		switch (RendererAPI::getName())
		{
		case RendererAPI::Name::None:
		default:
			COUT_ASSERT(0, "RendererAPI Name Not Found for IndexBuf");
			return nullptr;
		case RendererAPI::Name::OpenGL:
			return new GLIndexBuf(vertices, count);
		}
	}

	VertexArr * VertexArr::create()
	{
		switch (RendererAPI::getName())
		{
		case RendererAPI::Name::None:
		default:
			COUT_ASSERT(0, "RendererAPI Name Not Found for VertexBuf");
			return nullptr;
		case RendererAPI::Name::OpenGL:
			return new GLVertexArr();
		}
	}

	/* impl drawing ****************************************/


}

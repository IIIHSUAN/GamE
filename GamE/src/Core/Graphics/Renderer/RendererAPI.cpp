#include "pch.h"
#include "RendererAPI.h"

#include "OpenGL/GLRendererAPI.h"

namespace GE {

	void RendererAPI::init(Type apiType)
	{
		_type = apiType;

		switch (apiType)
		{
		case GE::RendererAPI::Type::OpenGL:
			_api = new GLRendererAPI();
			break;
		case GE::RendererAPI::Type::Directx:
			COUT_ASSERT(0, "[RendererAPI] NO Directx API");
			_api = nullptr;
			break;
		case GE::RendererAPI::Type::None:
		default:
			COUT_ASSERT(0, "[RendererAPI] NO API Type");
			_api = nullptr;
			break;
		}
	}

}
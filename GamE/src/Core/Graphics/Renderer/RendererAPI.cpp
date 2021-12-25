#include "pch.h"
#include "RendererAPI.h"

#include "OpenGL/GLRendererAPI.h"

namespace GE {

	RendererAPI::Type RendererAPI::_type = RendererAPI::Type::None;
	RendererAPI* RendererAPI::_api = nullptr;

	RendererAPI::~RendererAPI()
	{
		if (_api != nullptr)
			delete _api;
	}
	void RendererAPI::init(RendererAPI::Type apiType)
	{
		_type = apiType;

		switch (apiType)
		{
		case RendererAPI::Type::OpenGL:
			_api = new GLRendererAPI();
			break;
		case RendererAPI::Type::Directx:
			COUT_ASSERT(0, "[RendererAPI] NO Directx API");
			_api = nullptr;
			break;
		case RendererAPI::Type::None:
		default:
			COUT_ASSERT(0, "[RendererAPI] NO API Type");
			_api = nullptr;
			break;
		}
	}

}
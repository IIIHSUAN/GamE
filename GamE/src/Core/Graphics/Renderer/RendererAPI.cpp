#include "pch.h"
#include "RendererAPI.h"

#include "OpenGL/GLRendererAPI.h"

namespace GE {

	RendererAPI::Name RendererAPI::_name = RendererAPI::Name::None;
	RendererAPI* RendererAPI::_api = nullptr;

	RendererAPI::~RendererAPI()
	{
		if (_api != nullptr)
			delete _api;
	}
	void RendererAPI::init(RendererAPI::Name apiName)
	{
		_name = apiName;

		switch (apiName)
		{
		case RendererAPI::Name::OpenGL:
			_api = new GLRendererAPI();
			break;
		case RendererAPI::Name::Directx:
			COUT_ASSERT(0, "[RendererAPI] NO Directx API");
			_api = nullptr;
			break;
		case RendererAPI::Name::None:
		default:
			COUT_ASSERT(0, "[RendererAPI] API Name None");
			_api = nullptr;
			break;
		}
	}

}
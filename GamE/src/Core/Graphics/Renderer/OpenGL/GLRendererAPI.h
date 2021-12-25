#pragma once

#include "../RendererAPI.h"

namespace GE {

	class GLRendererAPI: public RendererAPI
	{
	public:

		virtual void setBackgroundColor(const glm::vec4& color) override;
		virtual void clear() override;
		virtual void draw(const std::shared_ptr<VertexArr>& vertexArr) override;
	};

}
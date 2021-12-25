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

	// above "Renderer" function set
	class RenderInstruction {
	public:
		inline static void draw(const std::shared_ptr<VertexArr>& vertexArr) { _api->draw(vertexArr); }

		static void setBackgroundColor();
		static void clear();
	private:
		static RendererAPI* _api;
	};
}
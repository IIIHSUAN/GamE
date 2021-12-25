#pragma once

#include <glm/glm.hpp>

#include "../Buffer/Buffer.h"

namespace GE {

	class RendererAPI
	{
	public:
		static enum class Type
		{
			None = 0, OpenGL = 1, Directx = 2
		};

		static void init(Type apiType);

		virtual void setBackgroundColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;
		virtual void draw(const std::shared_ptr<VertexArr>& vertexArr) = 0;

		inline RendererAPI::Type getType() { return _type; }
		inline static RendererAPI* get() { return _api; }
	private:
		static RendererAPI::Type _type;
		static RendererAPI* _api;
	};

	// above "Renderer" function set
	class RenderInstruction {
	public:
		inline static void draw(const std::shared_ptr<VertexArr>& vertexArr) { RendererAPI::get()->draw(vertexArr); }
	};
}
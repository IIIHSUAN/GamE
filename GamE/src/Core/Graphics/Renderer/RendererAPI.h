#pragma once

#include <glm/glm.hpp>

#include "../Buffer/Buffer.h"

namespace GE {

	class RendererAPI
	{
	public:
		virtual ~RendererAPI();

		enum class Name
		{
			None = 0, OpenGL = 1, Directx = 2
		};

		void init(RendererAPI::Name apiName);

		virtual void setBackgroundColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;
		virtual void draw(const std::shared_ptr<VertexArr>& vertexArr) = 0;

		inline static RendererAPI::Name getName() { return _name; }
		inline static RendererAPI* get() { return _api; }
	private:
		static RendererAPI::Name _name;
		static RendererAPI* _api;
	};

	// above "Renderer" function set
	class RenderInstruction {
	public:
		inline static  void init(RendererAPI::Name apiName) { RendererAPI::get()->init(apiName); }
		inline static void setBackgroundColor(const glm::vec4& color) { RendererAPI::get()->setBackgroundColor(color); }
		inline static void clear() { RendererAPI::get()->clear(); }
		inline static void draw(const std::shared_ptr<VertexArr>& vertexArr) { RendererAPI::get()->draw(vertexArr); }
	};
}
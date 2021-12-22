#pragma once

// sub compiler for shading

namespace GE {

	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() {};

		virtual void bind() const = 0;
	protected:
		uint32_t _renderer;
	};

}
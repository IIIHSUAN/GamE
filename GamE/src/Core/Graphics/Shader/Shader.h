#pragma once

#include <glm/glm.hpp>

// sub compiler for shading

namespace GE {

	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() {};

		virtual void bind() const = 0;

		// upload var to shader inside
		virtual void uploadUniMat4(const std::string& var_name, const glm::mat4 & mat) = 0;
	protected:
		uint32_t _shader;
	};

}
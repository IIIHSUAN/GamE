#pragma once

#include "../Shader.h"

namespace GE {

	class GLShader :public Shader
	{
	public:
		GLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~GLShader();

		virtual void bind() const override;
		virtual void uploadUniMat4(const std::string& var_name, const glm::mat4 & mat) override;
	private:
		std::string _vertexSrc, _fragmentSrc;
	};

}
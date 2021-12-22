#pragma once

#include "../Shader.h"

namespace GE {

	class GLShader :public Shader
	{
	public:
		GLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~GLShader();

		virtual void bind() const override;
	private:
		std::string _vertexSrc, _fragmentSrc;
	};

}
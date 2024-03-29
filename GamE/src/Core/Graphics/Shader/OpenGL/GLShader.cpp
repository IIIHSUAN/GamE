#include "pch.h"
#include "GLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace GE {

	GLShader::GLShader(const std::string & vertexSrc, const std::string & fragmentSrc) :_vertexSrc(vertexSrc), _fragmentSrc(fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = (const GLchar *)_vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			COUT_RED("GLShader compilation failed: {0}", infoLog.data());
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar *)_fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			COUT_RED("GLShader compilation failed: {0}", infoLog.data());
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_shader = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(_shader, vertexShader);
		glAttachShader(_shader, fragmentShader);

		// Link our program
		glLinkProgram(_shader);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_shader, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_shader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_shader);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			COUT_RED("GLShader linking failed: {0}", infoLog.data());
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(_shader, vertexShader);
		glDetachShader(_shader, fragmentShader);

	}
	GLShader::~GLShader()
	{
		glDeleteProgram(_shader);
	}
	void GLShader::bind() const
	{
		glUseProgram(_shader);

		// unbind -> glUseProgram(NULL);
	}
	void GLShader::uploadUniMat4(const std::string& var_name, const glm::mat4 & mat)  // make sure bind() before using
	{
		GLint var = glGetUniformLocation(_shader, var_name.c_str());
		glUniformMatrix4fv(var, 1, GL_FALSE, glm::value_ptr(mat));
	}
}
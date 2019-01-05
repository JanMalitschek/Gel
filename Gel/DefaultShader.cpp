#include "DefaultShader.h"

namespace Gel {

	DefaultShader::DefaultShader()
	{
		std::string vertexCode = "#version 440 core\n"
			"layout(location = 0) in vec3 position;\n"
			"layout(location = 1) in vec3 normal;\n"
			"layout(location = 2) in vec2 texCoords;\n"

			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"

			"out vec2 TexCoords;\n"

			"void main()\n"
			"{\n"
			"	gl_Position = projection * view * model * vec4(position, 1.0f);\n"
			"	TexCoords = texCoords;\n"
			"};";
		std::string fragmentCode = "#version 440 core\n"
			"out vec4 color;\n"

			"in vec2 TexCoords;\n"

			"void main()\n"
			"{\n"
			"	color = vec4(1.0, 0.0, 1.0, 1.0);\n"
			"}";
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar * fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// Print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// Print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		// Print linking errors if any
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void DefaultShader::Use()
	{
		glUseProgram(this->Program);
	}

	GLuint DefaultShader::GetProgram() {
		return this->Program;
	}
}
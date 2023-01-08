#include "pchOrange.h"
#include "Shader.h"

#include <glad/glad.h>


namespace Orange
{
	Shader::Shader(std::string_view vertexFilePath, std::string_view fragmentFilePath)
	{
		uint32_t vertexShader = CompileShader(vertexFilePath, GL_VERTEX_SHADER);
		uint32_t fragmentShader = CompileShader(fragmentFilePath, GL_FRAGMENT_SHADER);

		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		int  success;
		char infoLog[512];
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
			ORANGE_ASSERT(0, "Shader Program Linking failed! ERROR: {0}", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{

	}

	uint32_t Shader::GetID() const
	{
		return m_RendererID;
	}

	void Shader::Use(bool use) const
	{
		if (use)
		{
			glUseProgram(m_RendererID);
		}
		else
		{
			glUseProgram(0);
		}
	}

	uint32_t Shader::CompileShader(std::string_view shaderPath, int type)
	{
		// Load the Vertex Shader
		File file(shaderPath, OpenMode::Read);
		std::string source = file.Read();
		const char* vss = source.c_str();
		file.Close();

		uint32_t shader;
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &vss, NULL);
		glCompileShader(shader);

		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::string shaderName = "";
			switch (type)
			{
			case GL_VERTEX_SHADER: shaderName = "Vertex Shader";
				break;
			case GL_FRAGMENT_SHADER: shaderName = "Fragment Shader";
				break;
			}
			ORANGE_ASSERT(0, "'{0}' compilation failed! ERROR: {1}", shaderName, infoLog);
		}
		return shader;
	}	
}
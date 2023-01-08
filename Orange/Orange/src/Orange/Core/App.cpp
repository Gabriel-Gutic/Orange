#include "pchOrange.h"
#include "App.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"



namespace Orange
{
	App* App::s_Instance = nullptr;
	App::App()
		:m_IsRunning(true)
	{
		ORANGE_ASSERT(!s_Instance, "App already initialized!");
		s_Instance = this;

		m_Window = std::make_unique<Window>();
	}

	App::~App()
	{
	}

	void App::Run()
	{
		float vertices[] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			-0.5f,  0.5f,
			 0.5f,  0.5f,
		};

		uint32_t indices[] =
		{
			0, 1, 2,
			2, 1, 3,
		};

		unsigned int VBO;
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		unsigned int IBO;
		glGenBuffers(1, &IBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 Position;

void main()
{
	gl_Position = vec4(Position, 0.0f, 1.0f);
}

)";

		std::string fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}

)";

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vss = vertexShaderSource.c_str();
		glShaderSource(vertexShader, 1, &vss, NULL);
		glCompileShader(vertexShader);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fss = fragmentShaderSource.c_str();
		glShaderSource(fragmentShader, 1, &fss, NULL);
		glCompileShader(fragmentShader);

		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		while (m_IsRunning)
		{
			m_Window->Clear(Color::Blue);

			while (!m_EventQueue.empty())
			{
				Event& e = *m_EventQueue.front();
				
				if (e.GetType() == EventType::WindowClose)
				{
					Exit();
				}

				ORANGE_PRINT(e.ToString());

				PopEvent();
			}

			// Render Here

			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			glUseProgram(0);

			m_Window->SwapBuffers();
		}
	}

	void App::Exit()
	{
		m_IsRunning = false;
	}

	void App::PushEvent(Event* e)
	{
		s_Instance->m_EventQueue.push(e);
	}

	void App::PopEvent()
	{
		delete s_Instance->m_EventQueue.front();
		s_Instance->m_EventQueue.pop();
	}
}


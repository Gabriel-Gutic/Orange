#pragma once


namespace Orange
{
	class Shader
	{
	public:
		Shader(std::string_view vertexFilePath, std::string_view fragmentFilePath);
		~Shader();

		uint32_t GetID() const;

		void Use(bool use = true) const;
	private:
		static uint32_t CompileShader(std::string_view shaderPath, int type);
	private:
		uint32_t m_RendererID;
	};
}

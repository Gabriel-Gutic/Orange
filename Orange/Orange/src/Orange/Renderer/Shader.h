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

		int GetUniformLocation(const std::string& uniform) const;
		void SetMat3(const std::string& location, const Mat3& matrix);
		void SetFloat(const std::string& location, float f);
		void SetFloat2(const std::string& location, const Float2& f2);

		template <size_t SIZE>
		void SetIntArray(const std::string& location, const std::array<int, SIZE>& data);
		void SetIntData(const std::string& location, unsigned int size, const int* data);
	private:
		static uint32_t CompileShader(std::string_view shaderPath, int type);
	private:
		uint32_t m_RendererID;
		mutable std::unordered_map<std::string, int> m_UniformLocations;
	};

	template<size_t SIZE>
	inline void Shader::SetIntArray(const std::string& location, const std::array<int, SIZE>& data)
	{
		SetIntData(location, SIZE, data.data());
	}
}

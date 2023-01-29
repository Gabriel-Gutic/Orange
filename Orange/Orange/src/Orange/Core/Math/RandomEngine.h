#pragma once


namespace Orange
{
	class RandomEngine
	{
	private:
		RandomEngine();
	public:
		RandomEngine(const RandomEngine&) = delete;
		~RandomEngine();

		static void Initialize();
		static void Terminate();

		static RandomEngine& Get();

		int64_t RandomInt64(int64_t a = std::numeric_limits<int64_t>::min(), int64_t b = std::numeric_limits<int64_t>::max()) const;
		uint64_t RandomUInt64(uint64_t a = 0, uint64_t b = std::numeric_limits<uint64_t>::max()) const;
		int RandomInt(int a = std::numeric_limits<int>::min(), int b = std::numeric_limits<int>::max()) const;
		uint32_t RandomUInt(uint32_t a = 0, uint32_t b = std::numeric_limits<uint32_t>::max()) const;
		float RandomFloat(float a = 0.0f, float b = 1.0f) const;
	private:
		std::unique_ptr<std::random_device> m_Device;
		std::unique_ptr<std::mt19937> m_MT;

		static RandomEngine* s_Instance;
	};
}

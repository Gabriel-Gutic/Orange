#include "pchOrange.h"
#include "RandomEngine.h"


namespace Orange
{
	RandomEngine* RandomEngine::s_Instance = nullptr;

	RandomEngine::RandomEngine()
		:m_Device(nullptr), m_MT(nullptr)
	{
		m_Device = std::make_unique<std::random_device>();
		m_MT = std::make_unique<std::mt19937>((*m_Device)());
	}

	RandomEngine::~RandomEngine()
	{
	}

	void RandomEngine::Initialize()
	{
		ORANGE_ASSERT(!s_Instance, "RandomEngine already initialized!");
		s_Instance = new RandomEngine();
	}

	void RandomEngine::Terminate()
	{
		delete s_Instance;
	}

	RandomEngine& RandomEngine::Get()
	{
		return *s_Instance;
	}

	int64_t RandomEngine::RandomInt64(int64_t a, int64_t b) const
	{
		std::uniform_int_distribution<int64_t> distribution(a, b);
		int64_t random_int = distribution(*m_MT);
		return random_int;
	}

	uint64_t RandomEngine::RandomUInt64(uint64_t a, uint64_t b) const
	{
		std::uniform_int_distribution<uint64_t> distribution(a, b);
		uint64_t random_int = distribution(*m_MT);
		return random_int;
	}

	int RandomEngine::RandomInt(int a, int b) const
	{
		std::uniform_int_distribution<int> distribution(a, b);
		int random_int = distribution(*m_MT);
		return random_int;
	}

	uint32_t RandomEngine::RandomUInt(uint32_t a, uint32_t b) const
	{
		std::uniform_int_distribution<uint32_t> distribution(a, b);
		uint32_t random_int = distribution(*m_MT);
		return random_int;
	}

	float RandomEngine::RandomFloat(float a, float b) const
	{
		std::uniform_real_distribution<float> distribution(a, b);
		float random_float = distribution(*m_MT);
		return random_float;
	}

}
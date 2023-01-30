#include "pchOrange.h"
#include "UUID.h"


namespace Orange
{
	UUID::UUID(uint64_t first, uint64_t second)
	{
		if (first != 0ull)
			m_Data.first = first;
		else
		{
			do
			{
				m_Data.first = Math::RandomUInt64();
			} while (m_Data.first == 0ull);
		}
		if (second != 0ull)
			m_Data.second = second;
		else
		{
			do
			{
				m_Data.second = Math::RandomUInt64();
			} while (m_Data.second == 0ull);
		}
	}

	const std::pair<uint64_t, uint64_t>& UUID::GetData() const
	{
		return m_Data;
	}

	std::string UUID::ToString() const
	{
		std::stringstream ss;
		ss << std::hex << m_Data.first << m_Data.second;
		return ss.str();
	}

	bool operator==(const UUID& uuid1, const UUID& uuid2)
	{
		return uuid1.m_Data.first == uuid2.m_Data.first &&
			uuid1.m_Data.second == uuid2.m_Data.second;
	}

	std::ostream& operator<<(std::ostream& os, const UUID& uuid)
	{
		os << uuid.ToString();
		return os;
	}
}
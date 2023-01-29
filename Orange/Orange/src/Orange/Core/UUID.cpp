#include "pchOrange.h"
#include "UUID.h"


namespace Orange
{
	UUID::UUID()
	{
		m_Data.first = Math::RandomUInt64();
		m_Data.second = Math::RandomUInt64();
	}

	const std::pair<uint64_t, uint64_t>& UUID::GetData() const
	{
		return m_Data;
	}

	bool operator==(const UUID& uuid1, const UUID& uuid2)
	{
		return uuid1.m_Data.first == uuid2.m_Data.first &&
			uuid1.m_Data.second == uuid2.m_Data.second;
	}
}
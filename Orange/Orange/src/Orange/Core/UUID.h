#pragma once


namespace Orange
{
	class UUID
	{
	public:
		UUID(uint64_t first = 0ull, uint64_t second = 0ull);
		~UUID() = default;

		const std::pair<uint64_t, uint64_t>& GetData() const;
		std::string ToString() const;

		friend bool operator==(const UUID& uuid1, const UUID& uuid2);
		friend std::ostream& operator<<(std::ostream& os, const UUID& uuid);
	private:
		std::pair<uint64_t, uint64_t> m_Data;
	};
}

namespace std
{
	template<>
	struct hash<Orange::UUID>
	{
		size_t operator() (const Orange::UUID& uuid) const
		{
			auto [l, r] = uuid.GetData();
			return hash<uint64_t>()(l / 2ull + r / 2ull);
		}
	};
}

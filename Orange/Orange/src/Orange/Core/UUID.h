#pragma once


namespace Orange
{
	class UUID
	{
	public:
		UUID();
		~UUID() = default;

		const std::pair<uint64_t, uint64_t>& GetData() const;

		friend bool operator==(const UUID& uuid1, const UUID& uuid2);
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
			return hash<uint64_t>()(l / 2 + r / 2);
		}
	};
}

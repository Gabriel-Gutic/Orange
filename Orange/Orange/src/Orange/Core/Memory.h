#pragma once


namespace Orange
{
	template <typename T>
	T* Alloc(size_t count = 1)
	{
		try
		{
			if (count == 0)
				return nullptr;
			if (count == 1)
				return new T();
			return new T[count];
		}
		catch (std::bad_alloc)
		{
			ORANGE_ASSERT(0, "Failed to alloc memory!");
		}
		return nullptr;
	}
}
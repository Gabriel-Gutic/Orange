#pragma once
#include "Logger.h"


namespace Orange
{
	template <typename T>
	std::string ToString(const std::vector<T>& vec);
	template <typename T, size_t SIZE>
	std::string ToString(const std::array<T, SIZE>& arr);
	template <typename T>
	std::string ToString(const std::stack<T>& stack);
	template <typename T>
	std::string ToString(const std::queue<T>& queue);
	template <typename K, typename T>
	std::string ToString(const std::map<K, T>& map);
	template <typename K, typename T>
	std::string ToString(const std::unordered_map<K, T>& umap);
	template <typename T>
	std::string ToString(const std::set<T>& set);
	template <typename T>
	std::string ToString(const std::unordered_set<T>& uset);

	template<typename T>
	std::string ToString(const std::vector<T>& vec)
	{
		std::stringstream ss;
		ss << "[";
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (i != 0)
				ss << ", ";
			ss << vec[i];
		}
		ss << "]";
		return ss.str();
	}

	template<typename T, size_t SIZE>
	std::string ToString(const std::array<T, SIZE>& arr)
	{
		std::stringstream ss;
		ss << "[";
		for (size_t i = 0; i < arr.size(); i++)
		{
			if (i != 0)
				ss << ", ";
			ss << arr[i];
		}
		ss << "]";
		return ss.str();
	}

	template<typename T>
	std::string ToString(const std::stack<T>& stack)
	{
		std::stringstream ss;
		ss << "[";
		for (size_t i = 0; i < stack.size(); i++)
		{
			if (i != 0)
				ss << ", ";
			ss << stack[i];
		}
		ss << "]";
		return ss.str();
	}

	template<typename T>
	std::string ToString(const std::queue<T>& queue)
	{
		std::stringstream ss;
		ss << "[";
		for (size_t i = 0; i < queue.size(); i++)
		{
			if (i != 0)
				ss << ", ";
			ss << queue[i];
		}
		ss << "]";
		return ss.str();
	}

	template<typename K, typename T>
	std::string ToString(const std::map<K, T>& map)
	{
		std::stringstream ss;
		ss << "{";
		bool first = true;
		for (const auto& [key, obj] : map)
		{
			if (!first)
				ss << ", ";
			first = false;
			ss << "\"" << key << "\": \"" << obj << "\"";
		}
		ss << "}";
		return ss.str();
	}

	template<typename K, typename T>
	std::string ToString(const std::unordered_map<K, T>& umap)
	{
		std::stringstream ss;
		ss << "{";
		bool first = true;
		for (const auto& [key, obj] : umap)
		{
			if (!first)
				ss << ", ";
			first = false;
			ss << "\"" << key << "\": \"" << obj << "\"";
		}
		ss << "}";
		return ss.str();
	}

	template<typename T>
	std::string ToString(const std::set<T>& set)
	{
		std::stringstream ss;
		ss << "{";
		bool first = true;
		for (const auto& obj : set)
		{
			if (!first)
				ss << ", ";
			first = false;
			ss << obj;
		}
		ss << "}";
		return ss.str();
	}

	template<typename T>
	std::string ToString(const std::unordered_set<T>& uset)
	{
		std::stringstream ss;
		ss << "{";
		bool first = true;
		for (const auto& obj : uset)
		{
			if (!first)
				ss << ", ";
			first = false;
			ss << obj;
		}
		ss << "}";
		return ss.str();
	}
}


#ifdef DEBUG

#define PRINT(...)			Orange::Logger::GetCore()->info(__VA_ARGS__)
#define ERROR(...)			Orange::Logger::GetCore()->error(__VA_ARGS__)
#define WARNING(...)	    Orange::Logger::GetCore()->warn(__VA_ARGS__)
#define TRACE(...)			Orange::Logger::GetCore()->trace(__VA_ARGS__)
#define ASSERT(x, ...)	    if (!(x)) { ERROR(__VA_ARGS__); __debugbreak(); }


#define ORANGE_PRINT(...)			Orange::Logger::GetCore()->info(__VA_ARGS__)
#define ORANGE_ERROR(...)			Orange::Logger::GetCore()->error(__VA_ARGS__)
#define ORANGE_WARNING(...)			Orange::Logger::GetCore()->warn(__VA_ARGS__)
#define ORANGE_TRACE(...)			Orange::Logger::GetCore()->trace(__VA_ARGS__)
#define ORANGE_ASSERT(x, ...)	    if (!(x)) { ORANGE_ERROR(__VA_ARGS__); __debugbreak(); }

#else

#define PRINT(...)	
#define ERROR(...)	
#define WARNING(...)
#define TRACE(...)	
#define ASSERT(x, ...)  if (!(x));


#define ORANGE_PRINT(...)	
#define ORANGE_ERROR(...)	
#define ORANGE_WARNING(...)	
#define ORANGE_TRACE(...)	
#define ORANGE_ASSERT(x, ...)  if (!(x));


#endif // DEBUG

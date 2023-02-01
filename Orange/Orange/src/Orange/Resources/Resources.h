#pragma once
#include "Renderer/Texture.h"


namespace Orange
{
	class Resources
	{
	public:
		class Textures
		{
		public:
			static std::shared_ptr<Texture> Load(std::string_view texturePath, const std::string& resourceName = "");
			static void Add(const std::shared_ptr<Texture>& texture, const std::string& resourceName = "");
			static void Unload(const std::string& resourceName);
			static std::shared_ptr<Texture> Get(const std::string& resourceName);
			static const std::unordered_map<std::string, std::shared_ptr<Texture>>& GetAll();
		private:
			static std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;
		};
	};
}

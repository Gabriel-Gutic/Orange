#include "pchOrange.h"
#include "Resources.h"


namespace Orange
{
	std::unordered_map<std::string, std::shared_ptr<Texture>> Resources::Textures::s_Textures;

	std::shared_ptr<Texture> Resources::Textures::Load(std::string_view texturePath, const std::string& resourceName)
	{
		auto texture = Texture::CreateShared(texturePath);
		Add(texture, resourceName);

		return texture;
	}

	void Resources::Textures::Add(const std::shared_ptr<Texture>& texture, const std::string& resourceName)
	{
		std::string name;
		if (s_Textures.find(resourceName) != s_Textures.end() ||
			resourceName == "")
		{
			int i = 1;
			do
			{
				name = "Texture" + std::to_string(i++);
			} while (s_Textures.find(name) != s_Textures.end());
		}

		if (s_Textures.find(resourceName) != s_Textures.end() &&
			resourceName != "")
		{
			ORANGE_ERROR("A texture with name '{0}' already exists!"
				"The texture '{1}' will be created with the name '{2}'",
				resourceName, texture->GetFilepath(), name);
		}
		else if (resourceName != "")
		{
			name = resourceName;
		}
		s_Textures[name] = texture;
	}

	void Resources::Textures::Unload(const std::string& resourceName)
	{
		if (s_Textures.find(resourceName) == s_Textures.end())
			ORANGE_ERROR("Texture '{0}' does not exist!", resourceName);
		else
			s_Textures.erase(resourceName);
	}

	std::shared_ptr<Texture> Resources::Textures::Get(const std::string& resourceName)
	{
		if (s_Textures.find(resourceName) == s_Textures.end())
		{
			ORANGE_ASSERT("Texture '{0}' does not exist!", resourceName);
		}

		return s_Textures[resourceName];
	}

	const std::unordered_map<std::string, std::shared_ptr<Texture>>& Resources::Textures::GetAll()
	{
		return s_Textures;
	}
}
#pragma once
#include "Renderer/Vertex.h"
#include "Renderer/Texture.h"


namespace Orange
{
	struct SpriteRenderer
	{
		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<std::shared_ptr<Texture>> Textures;
	
		static std::string GetName();
	};
}

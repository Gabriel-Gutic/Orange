#include "pchOrange.h"
#include "Quad.h"

#include "Components/Components.h"
#include "Renderer/Renderer.h"


namespace Orange
{
	std::shared_ptr<GameObject> CreateQuad()
	{
		auto gameObject = std::make_shared<GameObject>();

		auto& renderer = gameObject->EmplaceComponent<SpriteRenderer>();

		renderer.Vertices = {
			Vertex({ -0.5f, -0.5f }, FColor::White, { 0.0f, 0.0f }),
			Vertex({  0.5f, -0.5f }, FColor::White, { 1.0f, 0.0f }),
			Vertex({ -0.5f,  0.5f }, FColor::White, { 0.0f, 1.0f }),
			Vertex({  0.5f,  0.5f }, FColor::White, { 1.0f, 1.0f })
		};

		renderer.Indices = {
			0, 1, 2,
			2, 1, 3
		};

		gameObject->SetName("Quad");
		gameObject->SetDrawFunction([](const GameObject& obj) {
			Renderer::DrawSprite(obj);
		});

		return gameObject;
	}

}
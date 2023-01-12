#include "pch.h"

class TileAppLayer : public Orange::Layer
{
public:
	TileAppLayer()
	{
		m_Texture = Orange::Texture::CreateShared("assets/Images/wild-chest.jpg");
	}

	~TileAppLayer()
	{

	}

	virtual void OnUpdate() override
	{
		//Orange::Renderer::DrawQuad(Orange::Float2(0.0f, 0.0f));

		Orange::Renderer::DrawTexture(m_Texture, Orange::Float2(0.0f, 0.0f));
	}

	virtual void OnEvent(const Orange::Event& e) override
	{

	}
private:
	std::shared_ptr<Orange::Texture> m_Texture;
};


class TileApp : public Orange::App
{
public:
	TileApp()
	{
		PushLayer(new TileAppLayer());
	}
};


Orange::App* Orange::App::Create()
{
	return Orange::Alloc<TileApp>();
}


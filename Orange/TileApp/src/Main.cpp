#include "pch.h"


class TileApp : public Orange::App
{
public:
	TileApp()
	{
	}
};


Orange::App* Orange::App::Create()
{
	return Orange::Alloc<TileApp>();
}


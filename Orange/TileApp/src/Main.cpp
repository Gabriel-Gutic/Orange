#include "pch.h"


class TileApp : public Orange::App
{
public:
	TileApp()
	{
		Orange::Mat3 M({1, 2, 3, 2, 2, 3, 1, 1, 0});
		PRINT(M.Determinant());
	}
};


Orange::App* Orange::App::Create()
{
	return Orange::Alloc<TileApp>();
}


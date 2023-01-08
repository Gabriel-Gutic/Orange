#include "pchOrange.h"

#include "App.h"


int main(int argc, char** args)
{
	Orange::Logger::Initialize();

	auto* app = Orange::App::Create();

	app->Run();

	delete app;

	return 0;
}
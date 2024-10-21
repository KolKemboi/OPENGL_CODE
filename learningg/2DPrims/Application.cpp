#include <memory>
#include "Engine.hpp"

int main()
{
	std::unique_ptr<Engine> MyEngine = std::make_unique<Engine>();

	MyEngine->Run();
}
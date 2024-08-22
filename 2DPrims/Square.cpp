#include "Engine.hpp"
#include <memory>

int main() {
	
	
	std::unique_ptr<Engine> Prims2D = std::make_unique<Engine>();

	Prims2D->Run();

	return 0;
}

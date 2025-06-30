#include <iostream>
#include <memory>
#include "entt/entt.hpp"
#include "toolbox/Engine.hpp"
int main() {
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->runEngine();
  return 0;
}

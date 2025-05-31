#include "toolbox/engine.h"
#include <memory>

int main() {
  std::unique_ptr<Engine> engine = std::make_unique<Engine>();
  engine->runEngine();
}

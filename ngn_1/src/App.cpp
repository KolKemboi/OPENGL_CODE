#include "toolbox/engine.h"
#include <memory>

int main(int argc, char *argv[]) {
  std::unique_ptr<Engine> myengine = std::make_unique<Engine>();
  myengine->runEngine();
  return 0;
}

#include "toolbox/engine.h"
#include <memory>


int main(){
  std::unique_ptr<Engine> myEngine = std::make_unique<Engine>();
  myEngine->runEngine();
}

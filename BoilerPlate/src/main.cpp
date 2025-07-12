#include "engine.h"
#include <memory>

int main()
{
    std::unique_ptr<Engine> myEngine = std::make_unique<Engine>();
    
    return 0;
}
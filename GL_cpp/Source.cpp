#include <entt/entt.hpp>
#include <iostream>

int main() {
    entt::registry registry;

    auto entity = registry.create();

    registry.emplace<int>(entity, 42); 

    int& value = registry.get<int>(entity);
    value = 100;

    std::cout << "Entity component value: " << value << std::endl;

    return 0;
}

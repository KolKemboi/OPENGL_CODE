#pragma once

#include <entt/entt.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {
public:
  Entity(entt::registry &reg);
  void RenderSystem(const glm::mat4 &view, const glm::mat4 &projection);

private:
  entt::entity m_Entity;
  entt::registry &m_Reg;
  struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
  };
};

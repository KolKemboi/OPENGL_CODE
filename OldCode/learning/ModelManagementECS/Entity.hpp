#pragma once

#include "Shader.hpp"
#include "Camera.hpp"
#include "ModelLoader.hpp"
#include <entt/entt.hpp>

typedef unsigned int u_int;

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

};


entt::entity createModelEntity(entt::registry& registry, const std::string& modelPath)
{
	entt::entity entity = registry.create();

	registry.emplace<_Mesh>(entity, CreateMesh(modelPath));
	registry.emplace<Transform>(entity, Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) });

	return entity;
}

void renderSystem(entt::registry& registry)
{
    registry.view<_Mesh, Transform>().each([](auto entity, _Mesh& mesh, Transform& transform) {
        glUseProgram(mesh.shader);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
        model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, transform.scale);

        glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(mesh.vertexArray);
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        });
}

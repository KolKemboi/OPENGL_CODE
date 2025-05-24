#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>
#include <iostream>

#include "MeshLoader.hpp"


typedef unsigned int u_int;

struct Transform {
    glm::vec3 position, rotation, scale;
};

entt::entity CreateEntity(entt::registry& registry, const std::string& path) {
    auto entity = registry.create();
    registry.emplace<Mesh>(entity, CreateMesh(path));
    registry.emplace<Transform>(entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    return entity;
}

void Render(entt::registry& registry, const glm::mat4& view, const glm::mat4& projection)
{
    registry.view<Mesh, Transform>().each([&](auto, Mesh& mesh, Transform& trans)
        {
            glUseProgram(mesh.shaderProgram);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), trans.position);
            model = glm::rotate(model, glm::radians(trans.rotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(trans.rotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(trans.rotation.z), glm::vec3(0, 0, 1));
            model = glm::scale(model, trans.scale);

            glUniformMatrix4fv(glGetUniformLocation(mesh.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(glGetUniformLocation(mesh.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(mesh.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

            glBindVertexArray(mesh.VAO);
            glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
    );
}


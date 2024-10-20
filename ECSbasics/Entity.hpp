#pragma once

#include "Shader.hpp"
#include "Camera.hpp"
#include "ModelLoader.hpp"
#include <entt/entt.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int u_int;

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation; // Assuming rotation in degrees
    glm::vec3 scale;
};

// Create an entity and add mesh and transform components
entt::entity CreateModelEntity(entt::registry& registry, const std::string& modelPath)
{
    entt::entity entity = registry.create();

    // Create the mesh using the model loader and set a default transform
    registry.emplace<Mesh>(entity, CreateMesh(modelPath));
    registry.emplace<Transform>(entity, Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) });

    return entity;
}

// Render system to process and render each entity with Mesh and Transform components
void RenderSystem(entt::registry& registry, const glm::mat4& view, const glm::mat4& projection)
{
    registry.view<Mesh, Transform>().each([&](auto entity, Mesh& mesh, Transform& transform) {
        // Use the shader program associated with the mesh
        glUseProgram(mesh.shader);

        // Create model matrix from position, rotation, and scale
        glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
        model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0)); // X-axis rotation
        model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0)); // Y-axis rotation
        model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1)); // Z-axis rotation
        model = glm::scale(model, transform.scale);

        // Send the model matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // Send the view and projection matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Bind the vertex array object and draw the mesh
        glBindVertexArray(mesh.vertexArray);
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        });
}

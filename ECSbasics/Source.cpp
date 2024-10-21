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
#include <stdexcept>
#include <typeinfo>
#include <unordered_map>

typedef unsigned int u_int;

class ECS {
public:
    ECS() = default;

    // Add component to an entity
    template <typename Component, typename... Args>
    void AddComponent(entt::entity entity, Args&&... args) {
        registry.emplace<Component>(entity, std::forward<Args>(args)...);
    }

    // Get a component from an entity
    template <typename Component>
    Component& GetComponent(entt::entity entity) {
        return registry.get<Component>(entity);
    }

    // Check if an entity has a particular component
    template <typename Component>
    bool HasComponent(entt::entity entity) {
        return registry.any_of<Component>(entity);
    }

    // Remove a component from an entity
    template <typename Component>
    void RemoveComponent(entt::entity entity) {
        registry.remove<Component>(entity);
    }

    // Create a new entity
    entt::entity CreateEntity() {
        return registry.create();
    }

    // Destroy an entity and its components
    void DestroyEntity(entt::entity entity) {
        registry.destroy(entity);
    }

    // Render all entities
    void RenderEntities(const glm::mat4& view, const glm::mat4& projection) {
        registry.view<Mesh, Transform>().each([&](auto, Mesh& mesh, Transform& trans) {
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
        });
    }

private:
    entt::registry registry;
};

struct Vertex {
    glm::vec3 Position, Normal;
};

struct Mesh {
    u_int VAO, VBO, EBO, shaderProgram;
    size_t indexCount;
};

struct Transform {
    glm::vec3 position, rotation, scale;
};

Mesh CreateMesh(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

    if (!scene || !scene->mRootNode) {
        std::cerr << "Error loading mesh: " << importer.GetErrorString() << std::endl;
        return {};
    }

    aiMesh* mesh = scene->mMeshes[0];
    std::vector<float> vertices;
    std::vector<u_int> indices;

    for (u_int i = 0; i < mesh->mNumVertices; i++) {
        vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z,
                                          mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
    }

    for (u_int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
    }

    Mesh m;
    glGenVertexArrays(1, &m.VAO);
    glGenBuffers(1, &m.VBO);
    glGenBuffers(1, &m.EBO);

    glBindVertexArray(m.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Shader shader;
    m.shaderProgram = shader.GetProgram();
    m.indexCount = indices.size();

    std::cout << "Mesh loaded with " << m.indexCount << " indices.\n";
    return m;
}

class Engine {
public:
    Engine() : m_Width(1280), m_Height(720) {
        init();
        auto entity = ecs.CreateEntity();
        ecs.AddComponent<Mesh>(entity, CreateMesh("untitled.obj"));
        ecs.AddComponent<Transform>(entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    }

    ~Engine() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Run() {
        while (!glfwWindowShouldClose(m_Window)) {
            if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(m_Window, true);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.1f, 0.3f, 1.0f);

            ecs.RenderEntities(glm::mat4(1.0f), glm::mat4(1.0f));

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }

private:
    GLFWwindow* m_Window;
    u_int m_Width, m_Height;
    ECS ecs;

    void init() {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_Window = glfwCreateWindow(m_Width, m_Height, "ECS", nullptr, nullptr);
        if (!m_Window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwDestroyWindow(m_Window);
            throw std::runtime_error("Failed to initialize GLAD");
        }
        glViewport(0, 0, m_Width, m_Height);
        glEnable(GL_DEPTH_TEST);
    }
};

int main() {
    try {
        Engine engine;
        engine.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

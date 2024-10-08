#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <entt/entt.hpp>

// Vertex structure
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

// Mesh class to store vertex data
class Mesh {
public:
    std::vector<Vertex> vertices;
    unsigned int VAO, VBO;

    Mesh(std::vector<Vertex>& vertices) : vertices(vertices) {
        setupMesh();
    }

    void Draw(const glm::mat4& modelMatrix, GLuint shaderProgram) {
        glBindVertexArray(VAO);
        // Set the model matrix in the shader
        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glBindVertexArray(0);
    }

private:
    void setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};

// Transform component
struct Transform {
    glm::vec3 Position;
    glm::vec3 Rotation; // Euler angles in degrees
    glm::vec3 Scale;

    Transform(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
        : Position(position), Rotation(rotation), Scale(scale) {}

    glm::mat4 GetModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around x-axis
        model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around y-axis
        model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around z-axis
        model = glm::scale(model, Scale);
        return model;
    }
};

// Mesh component to hold mesh data
struct MeshComponent {
    Mesh* mesh;

    MeshComponent(Mesh* m = nullptr) : mesh(m) {}
};

// Scene class to manage entities
class Scene {
public:
    Scene() {}

    void update() {
        // Update logic for all entities
        auto view = registry.view<Transform>();
        for (auto entity : view) {
            // You can apply your update logic here if necessary
            // For example, if you want to animate or transform the object
            auto& transform = view.get<Transform>(entity);
            // Example: Rotate the object over time (not fully implemented)
            transform.Rotation.y += 0.1f; // Rotate around y-axis
        }
    }

    void render(GLuint shaderProgram) {
        auto view = registry.view<MeshComponent, Transform>();
        for (auto entity : view) {
            auto& meshComponent = view.get<MeshComponent>(entity);
            auto& transform = view.get<Transform>(entity);
            if (meshComponent.mesh) {
                glm::mat4 modelMatrix = transform.GetModelMatrix();
                meshComponent.mesh->Draw(modelMatrix, shaderProgram); // Pass the model matrix to the draw method
            }
        }
    }

    void addEntity(const Transform& transform, Mesh* mesh) {
        auto entity = registry.create();
        registry.emplace<Transform>(entity, transform);
        registry.emplace<MeshComponent>(entity, mesh);
    }

private:
    entt::registry registry; // Entity registry
};

// Function to load models using Assimp
void loadModel(const std::string& path, Scene& scene) {
    Assimp::Importer importer;
    const aiScene* aiScene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Process each mesh in the scene
    for (unsigned int i = 0; i < aiScene->mNumMeshes; i++) {
        aiMesh* mesh = aiScene->mMeshes[i];
        std::vector<Vertex> vertices;

        // Process vertices
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;
            glm::vec3 vector;

            // Positions
            vector.x = mesh->mVertices[j].x;
            vector.y = mesh->mVertices[j].y;
            vector.z = mesh->mVertices[j].z;
            vertex.Position = vector;

            // Normals
            vector.x = mesh->mNormals[j].x;
            vector.y = mesh->mNormals[j].y;
            vector.z = mesh->mNormals[j].z;
            vertex.Normal = vector;

            // Texture coordinates
            if (mesh->mTextureCoords[0]) {
                glm::vec2 texCoord;
                texCoord.x = mesh->mTextureCoords[0][j].x;
                texCoord.y = mesh->mTextureCoords[0][j].y;
                vertex.TexCoords = texCoord;
            } else {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        // Create the mesh and add it to the scene
        Mesh* newMesh = new Mesh(vertices);
        scene.addEntity(Transform(), newMesh); // Add a new entity with the mesh
    }
}

// Callback for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Function to compile and link shaders
GLuint setupShaders() {
    // Vertex shader
    const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;
    layout(location = 2) in vec2 texCoord;

    out vec3 fragNormal;
    out vec2 fragTexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        fragNormal = normal;
        fragTexCoord = texCoord;
        gl_Position = projection * view * model * vec4(position, 1.0);
    })";

    // Fragment shader
    const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 color;

    in vec3 fragNormal;
    in vec2 fragTexCoord;

    void main() {
        color = vec4(1.0, 1.0, 1.0, 1.0); // Simple white color for now
    })";

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Link shaders to create a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL with Assimp and Entt", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set up shaders
    GLuint shaderProgram = setupShaders();

    // Create a scene
    Scene scene;
    loadModel("untitled.obj", scene); // Load your model here

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update the scene (you can call this to apply transformations or animations)
        scene.update();

        // Render the scene
        scene.render(shaderProgram);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();
    return 0;
}

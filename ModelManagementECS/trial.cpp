#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <entt/entt.hpp>

const char* VertexShader =
R"(
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = vec4(aPos, 1.0);
	Normal = aNorm;
}
)";


const char* FragmentShader =
R"(

out vec4 FragColor;

in vec3 Normal;

void main()
{
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)";


// Mesh Component Definition
struct Mesh {
    GLuint vertexArray; // Vertex Array Object
    GLuint vertexBuffer; // Vertex Buffer Object
    GLuint indexBuffer; // Index Buffer Object
    GLuint shader; // Shader program ID associated with this mesh
    size_t indexCount; // Number of indices in the mesh
};

// Transform Component Definition
struct Transform {
    glm::vec3 position; // Position of the entity
    glm::vec3 rotation; // Rotation of the entity (in degrees)
    glm::vec3 scale; // Scale of the entity
};

// Function to read shader code from a file
std::string LoadShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to create and compile shaders
GLuint CreateShader() {
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
   // std::string vertexSourceStr = LoadShaderSource(vertexPath);
    //const char* vertexSource = vertexSourceStr.c_str();
    glShaderSource(vertexShader, 1, &VertexShader, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //std::string fragmentSourceStr = LoadShaderSource(fragmentPath);
    //const char* fragmentSource = fragmentSourceStr.c_str();
    glShaderSource(fragmentShader, 1, &FragmentShader, nullptr);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Clean up shaders as they are now linked into the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Function to create and initialize a mesh using Assimp
Mesh CreateMesh(const std::string& modelPath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return Mesh{};
    }

    // Process the first mesh in the scene (you can modify this to handle multiple meshes)
    aiMesh* mesh = scene->mMeshes[0];
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Extract vertices and indices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D pos = mesh->mVertices[i];
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);

        // Texture coordinates (if present)
        if (mesh->mTextureCoords[0]) {
            aiVector3D texCoord = mesh->mTextureCoords[0][i];
            vertices.push_back(texCoord.x);
            vertices.push_back(texCoord.y);
        }
        else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh loadedMesh;

    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &loadedMesh.vertexArray);
    glBindVertexArray(loadedMesh.vertexArray);

    // Generate and bind the Vertex Buffer Object (VBO)
    glGenBuffers(1, &loadedMesh.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, loadedMesh.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Generate and bind the Index Buffer Object (EBO)
    glGenBuffers(1, &loadedMesh.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, loadedMesh.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers (assuming position + texture coordinates)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture Coords
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    // Create a shader for this mesh
    loadedMesh.shader = CreateShader();
    loadedMesh.indexCount = indices.size();

    return loadedMesh;
}

// Function to create a model entity
entt::entity CreateModelEntity(entt::registry& registry, const std::string& modelPath) {
    // Create a new entity in the registry
    entt::entity entity = registry.create();

    // Add Mesh and Transform components to the entity
    registry.emplace<Mesh>(entity, CreateMesh(modelPath));
    registry.emplace<Transform>(entity, Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) });

    return entity;
}

// Rendering System
void RenderSystem(entt::registry& registry) {
    registry.view<Mesh, Transform>().each([](auto entity, Mesh& mesh, Transform& transform) {
        // Use the shader program linked to this mesh
        glUseProgram(mesh.shader);

        // Set uniforms based on the transform (e.g., model matrix)
        glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
        model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, transform.scale);

        // Assuming there's a uniform named "model" in your shader
        glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // Bind the mesh's VAO and draw
        glBindVertexArray(mesh.vertexArray);
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        });
}

// Main function to demonstrate the setup
int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Model Loader", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    // Setup entity-component system registry
    entt::registry registry;

    // Create a model entity from an Assimp model
    CreateModelEntity(registry, "untitled.obj");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Render the scene
        RenderSystem(registry);

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwTerminate();
    return 0;
}

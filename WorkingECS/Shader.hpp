#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef unsigned int u_int;

static const char* vertexShader = R"(
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
out vec3 Normal;
uniform mat4 model, view, projection;
void main() {
    gl_Position = vec4(aPos, 1.0);
    Normal = aNorm;
})";

static const char* fragmentShader = R"(
out vec4 FragColor;
in vec3 Normal;
void main() {
    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
})";


class Shader
{
public:
    Shader() {
        m_VertexShader = createShader(GL_VERTEX_SHADER, vertexShader);
        m_FragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShader);
        m_ShaderProgram = createProgram(m_VertexShader, m_FragmentShader);
    }

    ~Shader() {
        glDeleteProgram(m_ShaderProgram);
    }

    void Use() const { glUseProgram(m_ShaderProgram); }
    unsigned int GetProgram() const { return m_ShaderProgram; }

private:
    u_int m_VertexShader, m_FragmentShader, m_ShaderProgram;
    u_int createShader(u_int type, const char* source) {
        u_int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        return shader;
    }
    u_int createProgram(u_int vertex, u_int fragment) {
        u_int program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return program;
    }

};

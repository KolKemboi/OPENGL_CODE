#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;
layout (location = 3) in vec3 norm;

out vec3 Color;
out vec3 Norm;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.0);
    
    Color = col;
    TexCoord = tex;
    
    Norm = mat3(transpose(inverse(model))) * norm;
}

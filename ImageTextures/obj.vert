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
    // Apply transformations: model -> view -> projection
    gl_Position = proj * view * model * vec4(pos, 1.0);
    
    // Pass the color, normal, and texture coordinates to the fragment shader
    Color = col;
    TexCoord = tex;
    
    // Transform the normal by the model matrix to bring it into world space
    Norm = mat3(transpose(inverse(model))) * norm;
}

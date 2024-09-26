#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    // Flip the texture coordinates horizontally
    TexCoord = vec2( 1.0 - aTexCoord.x,aTexCoord.y);
}

#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

void main()
{
    // Sample the texture using texCoords and assign the color to FragColor
    FragColor = texture(screenTexture, texCoords);
}
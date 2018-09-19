#version 330 core

layout (location = 0) in vec2 position;
uniform vec4 color;

out vec4 col;

void main()
{
    col = color;
    gl_Position = vec4(position, 0.0, 1.0);
}

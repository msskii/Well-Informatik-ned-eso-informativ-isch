#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv_pos;
out vec3 color;
out vec2 uv;

void main()
{
    uv = uv_pos;
    gl_Position = vec4(position, 0.0, 1.0);
}

#version 330 core

in vec4 col;
out vec4 color;

void main()
{
    color = col.abgr / 255.0f;
}

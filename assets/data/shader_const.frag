#version 330 core

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

void main()
{
    col = texture(texture_sampler, vec2(uv.x, uv.y)).bgra;
}

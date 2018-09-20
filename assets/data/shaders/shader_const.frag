#version 330 core

uniform sampler2D texture_sampler;

out vec4 col;
in vec2 uv;

void main()
{
    col = texture(texture_sampler, uv).bgra;
    // col = texture(texture_sampler, uv).rrra;
}

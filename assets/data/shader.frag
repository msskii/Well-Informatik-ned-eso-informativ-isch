#version 330 core

uniform sampler2D texture_sampler;
out vec4 col;
in vec2 uv;

void main()
{
    // col = vec4(1.0, 0.0, 1.0, 1.0);
    col = texture(texture_sampler, vec2(uv.x, 1 - uv.y)).bgra;
}

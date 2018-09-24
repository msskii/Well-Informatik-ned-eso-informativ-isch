#version 330 core

uniform sampler2D texture_sampler;

out vec4 col;
in vec2 uv;

void main()
{
    if(uv.x < 0 || uv.y < 0 || uv.x >= 1.0 || uv.y >= 1.0)
    {
        col = vec4(0, 0, 0, 0);
    }
    else
    {
        col = texture(texture_sampler, uv).bgra;
    }
    // col = texture(texture_sampler, uv).rrra;
}

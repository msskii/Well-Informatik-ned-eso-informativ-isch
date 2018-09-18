#version 330 core

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform vec2 mousepos;

void main()
{
    // col = vec4(1.0, 0.0, 1.0, 1.0);
    col = texture(texture_sampler, vec2(uv.x, 0.5 - uv.y)).bgra;
    float d = distance(vec2(mousepos.x * 4 - 1, 1 - mousepos.y * 4), pos) / sqrt(2);
    //col = (d * col) + (1.0 - d) * vec4(1, 1, 1, 1);
    col.a = 1.0 - d;
}

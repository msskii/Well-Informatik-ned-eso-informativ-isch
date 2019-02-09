#version 330 core

uniform sampler2D texture_sampler;

uniform vec4 col_mod; // argb

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
        
        col.a *= col_mod.x;
        col.r *= col_mod.y;
        col.g *= col_mod.z;
        col.b *= col_mod.w;
    }
}

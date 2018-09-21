#version 330 core

#define NUM_LIGHTS 40

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform float initial_alpha;
uniform vec3 ext_light_positions[NUM_LIGHTS]; // max 40 lights?
uniform vec3 ext_light_colors[NUM_LIGHTS]; // max 40 lights?

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
    float alpha = col.a * initial_alpha;
    float a = col.a;
    
    for(int i = 0; i < NUM_LIGHTS; i++)
    {
        if(ext_light_colors[i].x == 0x414570A3) continue;
        
        vec4 toAdd = vec4(ext_light_colors[i].x, ext_light_colors[i].y, ext_light_colors[i].z, alpha); // No alpha if there was no alpha...
        
        float d = distance(vec2(ext_light_positions[i].x * 2.0 - 1.0, (1.0 - ext_light_positions[i].y * 2.0) * 9.0 / 16.0), vec2(pos.x, pos.y / 16.0 * 9.0)) * 3.0;
        d = min(max(0, d), 1.0);
        toAdd *= (1.0 - d) * ext_light_positions[i].z * 3.0 / NUM_LIGHTS;
        
        col += toAdd;
    }
    
    col *= alpha;
    col.a = a;
}

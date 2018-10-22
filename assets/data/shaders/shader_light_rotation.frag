#version 330 core

#define NUM_LIGHTS 40

struct lightSource
{
    vec4 position; // Position on screen + brightness & radius
    vec4 color;
    float glowRatio; // Sunlight reflection
};

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform float initial_alpha;
layout (std140) uniform lightSources
{
    lightSource lights[NUM_LIGHTS]; // All the lights!
};

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
        if(lights[i].position.x == 0x414570A3) continue;
        
        vec4 toAdd = vec4(lights[i].color.x, lights[i].color.y, lights[i].color.z, alpha); // No alpha if there was no alpha...
        
        float d = distance(vec2(lights[i].position.x * 2.0 - 1.0, (1.0 - lights[i].position.y * 2.0) * 9.0 / 16.0), vec2(pos.x, pos.y / 16.0 * 9.0)) * 3.0 / lights[i].position.w;
        d = min(max(0, d), 1.0);
        toAdd *= (1.0 - d) * lights[i].position.z * 3.0 / NUM_LIGHTS;
        
        col += toAdd;
    }
    
    if(alpha >= 1.0) alpha = 1.0;
    
    col *= alpha;
    col.a = a;
}

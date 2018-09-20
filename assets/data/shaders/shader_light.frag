#version 330 core

#define NUM_LIGHTS 40

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform float initial_alpha;
uniform vec2 mousepos;
uniform vec3 ext_lights[NUM_LIGHTS]; // max 40 lights?

void main()
{
    col = texture(texture_sampler, uv).bgra;
    col.a = col.a; // min(initial_alpha, col.a); //1.0 - d;
    
    float modifier = initial_alpha;
    for(int i = 0; i < NUM_LIGHTS; i++)
    {
        float d = distance(vec2(ext_lights[i].x * 2 - 1, 1 - ext_lights[i].y * 2), vec2(pos.x, pos.y / 16.0 * 9.0));
        
        modifier += max(1.0 - d, 0) * ext_lights[i].z / 3.0; // Add to old light
    }
    col.rgb *= modifier / 3.0;
}

#version 330 core

#define NUM_LIGHTS 40

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform float initial_alpha;
uniform vec2 mousepos;
uniform vec3 ext_light_positions[NUM_LIGHTS]; // max 40 lights?
uniform vec3 ext_light_colors[NUM_LIGHTS]; // max 40 lights?

void main()
{
    col = texture(texture_sampler, vec2(uv.x, uv.y)).bgra;
    col.a = min(initial_alpha, col.a); //1.0 - d;
    
    float modifier = 0.0;
    for(int i = 0; i < NUM_LIGHTS; i++)
    {
        float d = distance(vec2(ext_light_positions[i].x * 2 - 1, 1 - ext_light_positions[i].y * 2), vec2(pos.x, pos.y / 16.0 * 9.0));
        
        modifier += max(1.0 - d, 0) * ext_light_positions[i].z / 3.0; // Add to old light
    }
    col.rgb *= modifier;
}

#version 330 core

#define NUM_LIGHTS 40

#define LIGHT_SPREAD 2.0
#define LIGHT_BRIGHTNESS 3.0

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform float initial_alpha;
uniform vec4 ext_light_positions[NUM_LIGHTS]; // max 40 lights? : x, y, brightness, radius
uniform vec4 ext_light_colors[NUM_LIGHTS]; // max 40 lights? r, g, b, a

void main()
{
    vec4 backcol;
    if(uv.x < 0 || uv.y < 0 || uv.x >= 1.0 || uv.y >= 1.0) backcol = vec4(0, 0, 0, 0);
    else backcol = texture(texture_sampler, uv).bgra;
    
    float alpha = initial_alpha;
    
    for(int i = 0; i < NUM_LIGHTS; i++)
    {
        if(ext_light_positions[i].x == 0x414570A3) continue;
        float d = distance(vec2(ext_light_positions[i].x * 2.0 - 1.0, (1.0 - ext_light_positions[i].y * 2.0) * 9.0 / 16.0), vec2(pos.x, pos.y / 16.0 * 9.0)) * LIGHT_SPREAD / ext_light_positions[i].w;
        d = min(max(0, d), 1.0);
        vec4 toAdd = ext_light_colors[i] * ext_light_colors[i].a / NUM_LIGHTS;
        if(toAdd.xyz == vec3(0, 0, 0)) alpha += (1.0 - d) * ext_light_colors[i].a / NUM_LIGHTS * ext_light_positions[i].z * LIGHT_BRIGHTNESS;
        else col += toAdd * (1.0 - d) * ext_light_positions[i].z * LIGHT_BRIGHTNESS;
    }
    
    
    float a = backcol.a;
    col = (alpha * backcol) + (col * (1.0 - alpha));
    col.a = a;
}

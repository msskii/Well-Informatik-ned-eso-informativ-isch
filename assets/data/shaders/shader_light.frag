#version 330 core

#define NUM_LIGHTS 40

#define LIGHT_SPREAD 2.0
#define LIGHT_BRIGHTNESS 3.0
#define LIGHT_EMIT_TO_REFLECT_RATIO 0.3

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

layout (std140) uniform lightSources {
    lightSource lights[NUM_LIGHTS];
};

uniform float initial_alpha;

void main()
{
    vec4 backcol;
    if(uv.x < 0 || uv.y < 0 || uv.x >= 1.0 || uv.y >= 1.0) backcol = vec4(0, 0, 0, 0);
    else backcol = texture(texture_sampler, uv).bgra;
     
    float alpha = initial_alpha;
    col = vec4(0,0,0,0);
    for(int i = 0; i < NUM_LIGHTS; i++)
    {
        // lights[i];
        
        if(lights[i].position.x == 0x414570A3) continue;
        float d = distance(vec2(lights[i].position.x * 2.0 - 1.0, (1.0 - lights[i].position.y * 2.0) * 9.0 / 16.0), vec2(pos.x, pos.y / 16.0 * 9.0)) * LIGHT_SPREAD / lights[i].position.w;
        d = min(max(0, d), 1.0);
        vec4 toAdd = lights[i].color * lights[i].color.a / NUM_LIGHTS;
        
        if(toAdd.xyz == vec3(0, 0, 0)) alpha += (1.0 - d) * lights[i].color.a / NUM_LIGHTS * lights[i].position.z * LIGHT_BRIGHTNESS;
        else col += toAdd * (1.0 - d) * lights[i].position.z * LIGHT_BRIGHTNESS;
    }
    
    if(alpha >= 1.0) alpha = 1.0;
    float a = backcol.a;
    
    //consists of sunlight hitting background + colored light hitting background + shine, the shine is not impacted by background brightness
    // col = (alpha * backcol) + (1 - light_emit_to_reflect_ratio) * backcol * (col * (1.0 - alpha)) + (light_emit_to_reflect_ratio * col * (1.0 - (alpha / 10)));

    col = (alpha * backcol) + backcol * (col * (1.0 - alpha)) + col * (1.0 - (alpha / 10));
    col.a = a;
}

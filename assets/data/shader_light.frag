#version 330 core

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform float initial_alpha;
uniform vec2 mousepos;
uniform vec3 ext_lights[40]; // max 40 lights?

void main()
{
    col = texture(texture_sampler, vec2(uv.x, 0.5 - uv.y)).bgra;
    col.a = initial_alpha; //1.0 - d;
    
    for(int i = 0; i < 10; i++)
    {
        float d = distance(vec2(ext_lights[i].x * 2 - 1, 1 - ext_lights[i].y * 2), vec2(pos.x, pos.y / 16.0 * 9.0));
        
        col.a += max(1.0 - d, 0) * ext_lights[i].z / 3.0; // Add to old light
        col.a = min(1.0, col.a); // Not over 1.0
    }
}

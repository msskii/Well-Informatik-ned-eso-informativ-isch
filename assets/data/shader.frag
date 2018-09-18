#version 330 core

uniform sampler2D texture_sampler;

in vec2 pos;
out vec4 col;
in vec2 uv;

uniform float initial_alpha;
uniform vec2 mousepos;
uniform vec2 ext_lights[40]; // max 10 lights?

void main()
{
    // col = vec4(1.0, 0.0, 1.0, 1.0);
    col = texture(texture_sampler, vec2(uv.x, 0.5 - uv.y)).bgra;
    // float d = distance(vec2(mousepos.x * 4 - 1, 1 - mousepos.y * 4), pos) / sqrt(2); // Distance from point to mouse
    col.a = initial_alpha; //1.0 - d;
    
    for(int i = 0; i < 10; i++)
    {
        float d = distance(vec2(ext_lights[i].x * 2 - 1, 1 - ext_lights[i].y * 2), pos) / 2;
        
        col.a += max(1.0 - d, 0) / 3;
        col.a = min(1.0, col.a);
        // col.a = max(col.a, 1.0 - d);
    }
}

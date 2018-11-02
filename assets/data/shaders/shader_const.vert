#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv_pos;

uniform vec3 rotation;
uniform vec2 screenSize;

out vec2 pos;
out vec3 color;
out vec2 uv;

void main()
{
    mat2 rot = mat2(cos(rotation.z), sin(rotation.z), -sin(rotation.z), cos(rotation.z));
    vec2 trans = vec2(rotation.x, rotation.y);
    
    vec2 dif = position - trans;
    dif.x /= screenSize.y;
    dif.y /= screenSize.x;
    trans.x /= screenSize.y;
    trans.y /= screenSize.x;
    vec2 outvec = dif * rot + trans;
        
    uv = uv_pos;
    pos = vec2(outvec.x * screenSize.y, outvec.y * screenSize.x);
    gl_Position = vec4(pos, 0.0, 1.0);
}

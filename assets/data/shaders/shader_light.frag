#version 330 core

#define NUM_LIGHTS 40
#define LIGHT_SPREAD 30.0
#define LIGHT_BRIGHTNESS 3.0
#define BACKGROUND_BRIGHTNESS 1.0

struct lightSource
{
    vec4 position; // Position on screen + brightness & radius
    vec4 color; // How much color is added from the light
    float glowRatio; // Sunlight reflection
};

uniform float displayAspect; // The aspect of the screen (Width / Height)
uniform sampler2D texture_sampler; // The current texture

in vec2 pos; // Current position
out vec4 col; // The color we calculate for that position
in vec2 uv; // Where in the texture we are

layout (std140) uniform lightSources // Pass a pointer to the lights and they all get transferred to the gpu
{
    lightSource lights[NUM_LIGHTS]; // All the lights!
};
uniform float initial_alpha; // The background alpha

void main()
{
    vec4 backcol; // Start with an empty background color
    if(uv.x < 0 || uv.y < 0 || uv.x >= 1.0 || uv.y >= 1.0) backcol = vec4(0, 0, 0, 0); // Out of bounds, so set it to black without any alpha
    else backcol = texture(texture_sampler, uv).bgra; // Load from the texture
    
    vec4 colorMod = backcol * BACKGROUND_BRIGHTNESS * initial_alpha; //Start with an empty color modifier
    float totalBrightness = backcol.a * BACKGROUND_BRIGHTNESS; // Background has a brightness of 10
    
    for(int i = 0; i < NUM_LIGHTS; i++) // For all lights do:
    {
        if(lights[i].position.x == 0x414570A3) continue; // Skip invalid lights
        
        float d = distance(vec2(lights[i].position.x * 2.0 - 1.0, (1.0 - lights[i].position.y * 2.0) / displayAspect), vec2(pos.x, pos.y / displayAspect)) * LIGHT_SPREAD / lights[i].position.z; // Calculate the distance from light to object, if both things were round
        d = min(max(0.0, d), 1.0); // Limit distance to range 0 to 1
        vec4 toAdd = lights[i].color * lights[i].color.a; // Calculate the light we want to add
        
        if(lights[i].color.xyz == vec3(0, 0, 0))
        {
            toAdd = vec4(1, 1, 1, 1);
        }
        
        //toAdd = lights[i].glowRatio * toAdd * (1.0 - initial_alpha) + backcol * (1.0 - lights[i].glowRatio) * toAdd * (1.0 - initial_alpha); // Modify the color to add with glow ratios
        
        colorMod += lights[i].position.w * toAdd * (1.0 - d); // Add the color modifier as many times as we indicate by brightness
        totalBrightness += lights[i].position.w * (1.0 - d); // Add the brightness of the light to the total amount
    }
    
    col = colorMod / totalBrightness;
    col.a = backcol.a; // If it was transparent, it should still be transparent
}

#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amplitude = 0.1;
uniform float freq = 1; // expressada en Hz 

const float PI = 3.141592;

uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    // Canvio el color a escala de grisos
    frontColor = vec4(N.z); // vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    vec3 dt = (amplitude*sin(2*PI*freq*time)) * normal; // A * sin(2π * f * t + ϴ)
    gl_Position = modelViewProjectionMatrix * vec4(vertex+dt, 1.0);
}

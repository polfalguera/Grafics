#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix; 
uniform mat4 modelViewMatrix;

uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

uniform float time;

uniform bool eyespace = false;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    
    float r = (distance(boundingBoxMax,boundingBoxMin))/2.0;
    
    float A = (r / 10.0);
    
    if (eyespace) A *= (modelViewMatrix*vec4(vertex,1.0)).y;
    else A *= vertex.y;
    
    vec3 dt = A * sin(time) * normal;    
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex+dt, 1.0);
}

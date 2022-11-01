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

uniform vec3 boundingBoxMin; // cantonada min de la capsa englobant
uniform vec3 boundingBoxMax; // cantonada max de la capsa englobant

uniform float time;

uniform bool eyespace = true;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0); //* N.z;
    vtexCoord = texCoord;
    
    // Càlcul de la diagonal de la capsa contenidora
    
    float diagonalBase = pow(boundingBoxMax.x-boundingBoxMin.x,2)+pow(boundingBoxMax.z-boundingBoxMin.z,2);
    diagonalBase = sqrt(diagonalBase);
    
    float diagonalCapsa = pow(diagonalBase,2)+pow(boundingBoxMax.y-boundingBoxMin.y,2);
    diagonalCapsa = sqrt(diagonalCapsa);
    
    // Càlcul de r
    
    float r = diagonalCapsa/2;
    
    float y = vertex.y;
    if (eyespace) y = (modelViewMatrix*vec4(vertex, 1.0)).y;
    
    // Càlcul amplitud d i la distància dt
    
    float d = (r/10.0)*y;
    vec3 dt = d * sin(time) * normal; // d * sin(2*PI*freq*time) * normal | on freq = 1/(2*PI) i per tant 2*PI*freq = 1
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex+dt, 1.0);
}

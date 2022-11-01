#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amp = 0.5;
uniform float freq = 0.25;
uniform float time;

const float PI = 3.141592;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    // Defineixo la sinusodial dt
    
    float dt = amp * sin(2*PI * freq * time + vertex.y); // Fase inicial es sin(vertex.y)
    
    // Declaro la matriu de rotació
    
    mat3 rotateMatrix = mat3(vec3(1,0,0),
    			     vec3(0,cos(dt),sin(dt)),
    			     vec3(0,-sin(dt),cos(dt))
    			    );
    			    
    vec3 rotatedVertex = rotateMatrix * vertex;
    
    gl_Position = modelViewProjectionMatrix * vec4(rotatedVertex, 1.0);
}

#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);//* N.z;
    vtexCoord = texCoord;
    
    // Calculo l'angle de rotació
    
    float theta = 0.4 * vertex.y * sin(time);
    
    mat3 rotateMatrix = mat3(vec3(cos(theta),0,-sin(theta)),
                             vec3(0,1,0),
                             vec3(sin(theta),0,cos(theta))
                            );
                            
    vec3 rotatedVertex = rotateMatrix * vertex;
    
    gl_Position = modelViewProjectionMatrix * vec4(rotatedVertex, 1.0);
}

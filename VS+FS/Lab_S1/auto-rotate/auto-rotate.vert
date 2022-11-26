#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float speed = 0.5;
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0); //* N.z; Per a que no es generin parts fosques.
    vtexCoord = texCoord;
    
    // Desclaro l'angle de rotació θ i la matriu de rotació
    
    float theta = time * speed;    
    
    mat3 rotateMatrix = mat3(vec3(cos(theta),0,-sin(theta)),
    			 vec3(0,1,0),
    			 vec3(sin(theta),0,cos(theta))
    			);
    			
    // Aplico la rotació al vertex abans de passar-lo a Eye space	
    
    vec3 rotatedVertex = rotateMatrix * vertex;    
    
    gl_Position = modelViewProjectionMatrix * vec4(rotatedVertex, 1.0);
}

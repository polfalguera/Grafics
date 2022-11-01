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
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    // Coordenades del vèrtex en clip space
    
    vec4 vertexClip = modelViewProjectionMatrix * vec4(vertex, 1.0);
    
    // Coordenades del vèrtex en NDC
    
    vec3 vertexNDC = vertexClip.xyz/vertexClip.w;
    
    // Factor d'escalat
    
    float factEsc = 0.5 + abs(sin(time));
    
    // El vertex final presentat en NDC al qual se li multiplica el factor d'escalar a les seves respectives x i y
    
    gl_Position = vec4(vec3(vertexNDC.x*factEsc,vertexNDC.y*factEsc,vertexNDC.z),1.0);
}

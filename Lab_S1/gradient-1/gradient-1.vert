#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin; // cantonada min de la capsa englobant
uniform vec3 boundingBoxMax; // cantonada max de la capsa englobant

const vec4 colors[5] = vec4[5] (
                        vec4(1.0,0.0,0.0,1.0), //red
                        vec4(1.0,1.0,0.0,1.0), //yellow
                        vec4(0.0,1.0,0.0,1.0), //green
                        vec4(0.0,1.0,1.0,1.0), //cian
                        vec4(0.0,0.0,1.0,1.0));//blue

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    
    // Atribueixo els colors depenent de la posició Y del vertex
    
    float interval = (boundingBoxMax.y-boundingBoxMin.y)/4; // Entre 4 ==> 1.blue-cian 2.cian-green 3.green-yellow 4.yellow-red
    float position = (vertex.y-boundingBoxMin.y)/interval; // Quants intervals caben entre boundingBoxMin.y i vertex.y
    
    // Part entera de la posició ==> interval en el que es troba
    // Part fraccional de la posició ==> porcentatge de cada color per a la interpolació
    
    int c = int(position);
    
    frontColor = mix(colors[c],colors[c+1],fract(position));
    
    //frontColor = vec4(newColor,1.0); //* N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

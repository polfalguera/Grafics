#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const vec4 colors[5] = vec4[5] (
                        vec4(1.0,0.0,0.0,1.0), //red
                        vec4(1.0,1.0,0.0,1.0), //yellow
                        vec4(0.0,1.0,0.0,1.0), //green
                        vec4(0.0,1.0,1.0,1.0), //cian
                        vec4(0.0,0.0,1.0,1.0));//blue

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    //frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    
    // Divideixo les components x,y,z per la component homogènia w
    
    vec3 vertexNDC = gl_Position.xyz/gl_Position.w;
    
    // Atribueixo als colors segons el valor de y, que oscil·la entre 1 i -1
    
    // L'interval de colors sera des de 1 a -1, per tant tamany 2, dividit entre 4 franjes = 2/4 = 0.5
    // Li sumo 1 per simular en comptes de entre 1 i -1 com si fos entre 0 i 2
    
    float position = (vertexNDC.y+1)/0.5;
    
    int i = int(position);
    
    frontColor = mix(colors[i],colors[i+1],fract(position));
    
    
}

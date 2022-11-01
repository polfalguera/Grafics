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
float esc = 0.5+abs(sin(time));

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    vec4 VS = modelViewProjectionMatrix * vec4(vertex, 1.0);
    VS = VS/VS.w ;
    
    VS = vec4(VS.x*esc,VS.y*esc,VS.z,VS.w);
    
    gl_Position = VS;
}

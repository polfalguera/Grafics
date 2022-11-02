#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float angle = 0.5;

mat3 rotacio = mat3(
                    vec3(cos(angle),0.0,-sin(angle)),
                    vec3(0.0,1.0,0.0),
                    vec3(sin(angle),0.0,cos(angle))
                );

void main()
{
    //vec3 N = normalize(normalMatrix * normal);
    vec3 rotNormal = rotacio * normal;
    vec3 rotVertex = rotacio * vertex;

    float t = smoothstep(1.45,1.55,vertex.y);

    vec3 newVertex = mix(vertex,rotVertex,t);
    vec3 newNormal = mix(normal,rotNormal,t);

    newNormal = normalize(normalMatrix*newNormal);

    frontColor = vec4(vec3(newNormal.z),1.0);

    gl_Position = modelViewProjectionMatrix * vec4(newVertex,1.0);
}

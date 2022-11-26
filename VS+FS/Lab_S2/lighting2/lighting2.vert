#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;

vec4 get_light(vec3 N, vec3 V, vec3 L) 
{

    vec3 R = normalize(2 * dot(N,L) * N-L);

    float NdotL = max(0.0,dot(N,L));
    float RdotV = max(0.0,dot(R,V));

    vec4 ambient = matAmbient * lightAmbient;

    vec4 diffuse = matDiffuse * lightDiffuse * NdotL; 

    vec4 specular = vec4(0.0);

    if (NdotL != 0.0) specular = matSpecular * lightSpecular * pow(RdotV,matShininess);

    return ambient+diffuse+specular;
}

void main()
{
    vec3 vertexSCO = (modelViewMatrix*vec4(vertex,1.0)).xyz; // Posició del vertex/punt P en SCO

    vec3 N = normalize(normalMatrix * normal);
    vec3 V = normalize(vec3(0.0,0.0,0.0) /*coord del obs en SCO*/ - vertexSCO);
    vec3 L = normalize(lightPosition.xyz - vertexSCO);

    frontColor = get_light(N,V,L);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

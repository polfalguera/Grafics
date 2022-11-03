#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


uniform mat4 modelMatrix;

uniform float t = 0.4;
uniform float scale = 4.0;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;

    float c = mix(boundingBoxMin.y,boundingBoxMax.y,t);

    vec3 V = vertex; 

    if (step(c,V.y) == 0) V.y *= scale;
    else {
        float delta = c*scale - c;
        V.y += delta;
    }

    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}

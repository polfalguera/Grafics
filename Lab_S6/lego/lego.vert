#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 vfrontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const vec3[5] colors = vec3[5] (
                        vec3(0.9,0.2,0.1), //RED
                        vec3(0.0,1.0,0.0), //GREEN
                        vec3(0.0,0.0,1.0), //BLUE
                        vec3(0.0,1.0,1.0), //CIAN
                        vec3(1.0,1.0,0.0)  //YELLOW
                    );

vec4 calcularColor() {
    vec3 colorRes = colors[0];
    float minDist = distance(color,colors[0]);
    for (int i = 1; i < 5; ++i) {
        float dist = distance(color,colors[i]);
        if (dist < minDist) {
            colorRes = colors[i];
            minDist = dist;
        }
    }
    return vec4(colorRes,1.0);
}

void main()
{
    //vec3 N = normalize(normalMatrix * normal);
    vfrontColor = calcularColor();
    vtexCoord = texCoord;
    gl_Position = vec4(vertex, 1.0);
}

#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;
in vec3 P;

uniform float edge0 = 0.35;
uniform float edge1 = 0.4;

const vec4 WHITE = vec4(1.0);
const vec4 BLACK = vec4(vec3(0.0),1.0);

void main()
{
    vec3 V = -P;
    V = normalize(V);
    vec3 Nnorm = normalize(N);

    float c = dot(N,V);

    /*if (c < edge0) fragColor = BLACK;
    else if (c > edge1) fragColor = WHITE;
    else fragColor = vec4(0.8);*/

   float f = smoothstep(edge0,edge1,c);

   fragColor = mix(BLACK,WHITE,f);
}

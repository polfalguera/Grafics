#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D smile;

const vec4 BLACK = vec4(vec3(0.0),1.0);

in vec3 N;

void main()
{
    vec2 d = vec2(N.x,N.y) * -0.1;

    vec2 C1 = vec2(0.34,0.66);
    vec2 C2 = vec2(0.66,0.66);

    C1 += d;
    C2 += d;
    
    if ((distance(vtexCoord,C1)) <= 0.05) fragColor = BLACK;
    else if ((distance(vtexCoord,C2)) <= 0.05) fragColor = BLACK;
    else fragColor = texture(smile,vtexCoord);
}

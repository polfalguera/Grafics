#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

const vec4 black = vec4(vec3(0.0),1.0);
const vec4 grey  = vec4(0.8);

uniform float n = 8;

void main()
{
    float s = vtexCoord.s;
    float t = vtexCoord.t;

    float x = fract(s * n);
    float y = fract(t * n);
    if (x > 0.1 && y > 0.1) fragColor = grey;
    else fragColor = black;
}

#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

const vec4 black = vec4(vec3(0.0),1.0);
const vec4 grey  = vec4(0.8);
const float slice = 1.0 / 8.0;

void main()
{
    float s = vtexCoord.s;
    float t = vtexCoord.t;

    if (int(mod(s / slice,2.0)) == int(mod(t / slice,2.0))) fragColor = grey;
    else fragColor = black;
}

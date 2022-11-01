#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

const vec4 red = vec4(1.0,0.0,0.0,1.0);
const vec4 white = vec4(1.0,1.0,1.0,1.0);

uniform bool classic = false;

const float PI = 3.141592;

const float phi = PI/16;

void main()
{
    vec2 C = vec2(0.5,0.5);

    float d = distance(vtexCoord,C);
    float w = length(vec2(dFdx(d),dFdy(d)));
    float f = smoothstep(0.2-w,0.2+w,d);

    fragColor = mix(red,white,f); 

    if (!classic) {
        vec2 u = vtexCoord-C;
        float theta = atan(u.t,u.s);

        if (mod((theta / phi)+0.5,2) < 1  || d <= 0.2) fragColor = red;
        else fragColor = white;
    }
}

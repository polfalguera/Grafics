#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D fbm0;

uniform float time;

const float PI = 3.14159;

const vec4 RED     = vec4(1.0,0.0,0.0,1.0);
const vec4 YELLOW  = vec4(1.0,1.0,0.0,1.0);
const vec4 GREEN   = vec4(0.0,1.0,0.0,1.0);
const vec4 CYAN    = vec4(0.0,1.0,1.0,1.0);
const vec4 BLUE    = vec4(0.0,0.0,1.0,1.0);
const vec4 MAGENTA = vec4(1.0,0.0,1.0,1.0);

const float div = 1.0 / 3.0;

void main() 
{
    vec4 fbm = texture(fbm0,vtexCoord);

    float r = fbm.r;

    float A = 1.0;

    float f = 0.1;

    float phi = 2 * PI * r;

    float v = A * sin(2 * PI * f * time + phi);

    v = 3*(v+1);

    if (v < 1) fragColor = mix(RED,YELLOW,fract(v));
    else if (v < 2) fragColor = mix(YELLOW,GREEN,fract(v));
    else if (v < 3) fragColor = mix(GREEN,CYAN,fract(v));
    else if (v < 4) fragColor = mix(CYAN,BLUE,fract(v));
    else if (v < 5) fragColor = mix(BLUE,MAGENTA,fract(v));
    else fragColor = mix(MAGENTA,RED,fract(v));
    
}

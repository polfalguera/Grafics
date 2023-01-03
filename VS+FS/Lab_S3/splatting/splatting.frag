#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//uniform sampler2D myMap;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

in vec2 vtexCoord;

void main()
{
    vec4 noise = texture (noise0, vtexCoord);
    vec4 rock  = texture (rock1, vtexCoord);
    vec4 grass = texture (grass2, vtexCoord);

    fragColor = mix(rock,grass,noise.r);
}

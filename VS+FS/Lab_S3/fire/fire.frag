#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;

uniform float time;

uniform float slice = 0.1;

void main()
{
    //fragColor = frontColor;
    int id = int(mod(time / slice, 4));

    if (id == 0) fragColor = texture(sampler0,vtexCoord);
    else if (id == 1) fragColor = texture(sampler1,vtexCoord);
    else if (id == 2) fragColor = texture(sampler2,vtexCoord);
    else fragColor = texture(sampler3,vtexCoord);
}


/*
t    sampler
0.0  0
0.1  1
0.2  2
0.3  3
0.4  0
0.5  1
0.6  2
0.7  3
0.8  0
0.9  1
1    2
1.1  3
1.2  0
1.3  1
1.4  2
1.5  3
1.6  0
1.7  1
1.8  2
1.9  3 
2    0
*/
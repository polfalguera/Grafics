#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

void main()
{
    vec2 C = vec2(0.3,0.05);

    if (distance(vtexCoord,C) <= 0.05) fragColor = vec4(1.0);
    else fragColor = vec4(vec3(0.0),1.0);

    for (int i = 0; i < 10; ++i) {
        if (distance(vtexCoord,C) <= 0.05) fragColor = vec4(1.0);
        C += vec2(0.0,0.1); 
    }

    C = vec2(0.4,0.95);

    for (int i = 0; i < 3; ++i) {
        if (distance(vtexCoord,C) <= 0.05) fragColor = vec4(1.0);
        C += vec2(0.1,0.0);
    }

    C = vec2(0.7,0.85);

    for (int i = 0; i < 3; ++i) {
        if (distance(vtexCoord,C) <= 0.05) fragColor = vec4(1.0);
        C -= vec2(0.0,0.1); 
    }

    C = vec2(0.4,0.55);

    for (int i = 0; i < 3; ++i) {
        if (distance(vtexCoord,C) <= 0.05) fragColor = vec4(1.0);
        C += vec2(0.1,0.0);
    }
}

#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int mode = 2;

const vec4 WHITE = vec4(1.0);
const vec4 BLACK = vec4(vec3(0.0),1.0);
const vec4 GREY  = vec4(vec3(0.8),1.0);
const vec4 SKIN  = vec4(vec3(1.0,0.8,0.6),1.0);

in vec2 vtexCoord;

float d1, d2, d3, w, f;

void main()
{
    vec2 C1 = vec2(0.5,0.4);
    vec2 C2 = vec2(0.2,0.8);
    vec2 C3 = vec2(0.8,0.8);

    d1 = distance(vtexCoord,C1);
    d2 = distance(vtexCoord,C2);
    d3 = distance(vtexCoord,C3);
    if (d1 <= 0.35 || d2 <= 0.2 || d3 <= 0.2) {
        fragColor = BLACK;
    }
    else fragColor = GREY;

    if (mode > 0) {
        C1 = vec2(0.5,0.6);
        C2 = vec2(0.9,0.45);
        C3 = vec2(1.1,0.45);

        d1 = distance(vec2(vtexCoord.x,vtexCoord.y*2),C1);
        d2 = distance(vec2(vtexCoord.x*2,vtexCoord.y),C2);
        d3 = distance(vec2(vtexCoord.x*2,vtexCoord.y),C3);
        if (d1 <= 0.3 || d2 <= 0.25 || d3 <= 0.25) {
            fragColor = SKIN;
        }

        if (mode == 2) {
            C1 = vec2(0.9,0.5);
            C2 = vec2(1.1,0.5);

            d1 = distance(vec2(vtexCoord.x*2,vtexCoord.y),C1);
            d2 = distance(vec2(vtexCoord.x*2,vtexCoord.y),C2);

            if (d1 <= 0.15 || d2 <= 0.15) {
                fragColor = WHITE;
            }

            C1 = vec2(0.9,0.44);
            C2 = vec2(1.1,0.44);

            d1 = distance(vec2(vtexCoord.x*2,vtexCoord.y),C1);
            d2 = distance(vec2(vtexCoord.x*2,vtexCoord.y),C2);
            if (d1 <= 0.075 || d2 <= 0.075) {
                fragColor = BLACK;
            }

            
        }
    }

}

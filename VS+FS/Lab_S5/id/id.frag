#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D digits;

void main()
{
    vec2 newCoord = vtexCoord;

    float n = 1.0 / 6.0;
    float m = 1.0 / 10.0;

    if (newCoord.s <= n) {
        newCoord.s = fract(vtexCoord.s*6.0)*m + 0.4;
    }
    else if (newCoord.s <= 2*n) {
        newCoord.s = fract(vtexCoord.s*6.0)*m + 0.8;
    }
    else if (newCoord.s <= 3*n) {
        newCoord.s =  fract(vtexCoord.s*6.0)*m;
    }
    else if (newCoord.s <= 4*n) {
        newCoord.s = fract(vtexCoord.s*6.0)*m + 0.9;
    }
    else if (newCoord.s <= 5*n) {
        newCoord.s = fract(vtexCoord.s*6.0)*m + 0.4;
    }
    else if (newCoord.s <= 6*n) {
        newCoord.s = fract(vtexCoord.s*6.0)*m + 0.2;
    }

    fragColor = texture(digits,newCoord);

    if (fragColor.a != 1) discard;
    else fragColor = vec4(0.0,0.0,1.0,1.0);
}

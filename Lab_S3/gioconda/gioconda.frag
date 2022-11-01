#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D gioconda;

uniform float time;

const vec2 eye = vec2(0.41, 1-0.31);
const vec2 offset = vec2(0.01, 1-0.19);

void main()
{
    vec2 vtexCoord2 = vtexCoord;

    if (fract(time) > 0.5) {
        float off = length(vtexCoord2-eye);
        if (off <= 0.025) vtexCoord2 += offset;
    }

    fragColor = texture(gioconda,vtexCoord2);
}

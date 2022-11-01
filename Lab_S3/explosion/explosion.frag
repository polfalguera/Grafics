#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D explosion;
in vec2 vtexCoord;

uniform float time;
const float slice = 1.0 / 30.0;

void main()
{
    vec2 texCoord = vec2(1.0/8.0,1.0/6.0) * vtexCoord; // frame[40] ==> s[0,1/8] t[0,1/6]
    texCoord.t +=  1 - 1.0/6.0; // Posició inicial: frame[0] ==> s[0,1/8] t[5/6,1]

    int frame = int(mod(time / slice,48)); // En cas que arribi al final (frame[47]), aleshores torna a començar pel frame[00]

    int ds = int(mod(frame,8)); // Per saber en quina columna em trobo (0..7)
    int dt = frame / 8; // En la primera fila, 0..7 / 8..8 = 0 (fila 0) || En la segona, 8..15 / 8..8 = 1 (fila 1) || ........

    texCoord.s += ds * 1.0 / 8.0;
    texCoord.t -= dt * 1.0 / 6.0;

    fragColor = texture(explosion, texCoord);     
    fragColor = fragColor.a * fragColor;
}

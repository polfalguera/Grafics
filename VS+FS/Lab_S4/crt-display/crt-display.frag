#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 fragCoord;

uniform int n = 4;
void main()
{
    if (int(mod(gl_FragCoord.y,n)) == 0) fragColor = frontColor;
    else discard;
}

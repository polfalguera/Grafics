#version 330 core

in vec2 gtexCoord;
in vec4 gfrontColor;
in vec3 gnormal;
in float caraSuperior;

out vec4 fragColor;

uniform sampler2D lego;

void main()
{
    if (caraSuperior == 1) fragColor = gfrontColor * texture(lego,gtexCoord);
    else fragColor = gfrontColor;
}
#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;

in vec2 gtexCoord;
uniform sampler2D colormap;

void main()
{
    if (gtexCoord.s >= 0) {
        vec4 color = texture(colormap,gtexCoord);
        if (color.w >= 0.1) fragColor = color * color.w;
        else discard;
    }
    else fragColor = gfrontColor;
}

#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

float rx = 4.0/3.0;


void main()
{
    // Primera bandera //
    /*
    if (vtexCoord.s <= 0.5) fragColor = vec4(0.0,0.8,1.0,1.0);
    else if (vtexCoord.t <= 0.5) fragColor = vec4(1.0,1.0,0.0,1.0);
    else fragColor = vec4(1.0,0.0,0.0,1.0);
    */

    //if (vtexCoord.s <= 0.1 && vtexCoord.t <= 0.1) fragColor = vec4(1.0,0.0,0.0,1.0);
    //else if (vtexCoord.s <= 0.2 && vtexCoord.t <= 0.2) fragColor = vec4(1.0,1.0,0.0,1.0);


    // Segona bandera //
    /*
    vec2 C = vec2(0.5*4.0/3.0,0.5*3.0/4.0);
    vec2 aux = vec2(4.0/3.0,3.0/4.0) * vtexCoord;
    if (distance(aux,C) <= 0.275) fragColor = vec4(1.0,0.0,0.0,1.0);
    else if (vtexCoord.t <= 0.35) fragColor = vec4(0.0,0.5,0.7,1.0);
    else if (vtexCoord.t <= 0.65) fragColor = vec4(1.0,1.0,0.0,1.0);
    else fragColor = vec4(0.1,0.7,0.3,1.0);
    */

    // Tercera bandera //

    vec2 C1 = vec2(0.275*4.0/3.0,0.5*3.0/4.0);
    vec2 C2 = vec2(0.41*4.0/3.0,0.5*3.0/4.0);
    vec2 aux = vec2(vtexCoord.s*4.0/3.0,vtexCoord.t*3.0/4.0);
    if (vtexCoord.s >= 0.6 && vtexCoord.s <=0.85 && vtexCoord.t >= 0.3 && vtexCoord.t <= 0.75) fragColor = vec4(1.0);
    else if (distance(aux,C1) <= 0.3) fragColor = vec4(1.0);
    else fragColor = vec4(0.4,0.65,0.4,1.0);

    if (distance(aux,C2) <= 0.3 && aux.s <= C2.x+0.2) fragColor = vec4(0.4,0.65,0.4,1.0);
    
}

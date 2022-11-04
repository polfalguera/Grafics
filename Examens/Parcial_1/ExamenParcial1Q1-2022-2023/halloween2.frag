#version 330 core

in vec4 frontColor;
out vec4 fragColor;

const vec4 ORANGE = vec4(1.0,0.7,0.0,1.0);
const vec4 BLACK  = vec4(vec3(0.0),1.0);

in vec2 vtexCoord;

void main()
{
    //FONS TARONJA
    vec2 C1 = vec2(0.5,0.5);

    float r1 = 0.4;

    float d1 = distance(C1,vtexCoord);
    
    float w = 0.1;
    float f = smoothstep(r1-w,r1+w,d1);

    fragColor = mix(ORANGE,BLACK,f); 

    if (vtexCoord.s> 0.46 && vtexCoord.s < 0.53 && vtexCoord.y > 0.7 && vtexCoord.y < 0.9) fragColor = BLACK;	

    //CARBASSA
    vec2 C2 = vec2(0.5,0.5);
    vec2 C3 = vec2(0.4,0.6);
    vec2 C4 = vec2(0.6,0.6);

    float r2 = 0.3;
    float r3 = 0.08;
    float r4 = 0.08;

    float d2 = distance(C2,vtexCoord);
    float d3 = distance(C3,vtexCoord);
    float d4 = distance(C4,vtexCoord);

    if (step(r2,d2) == 0 && step(r3,d3) != 0 && step(r4,d4) != 0) fragColor = BLACK;

    //SOMRIURE
    vec2 C5 = vec2(0.5,0.5);
    vec2 C6 = vec2(0.5,0.55);


    float r5 = 0.2;
    float r6 = 0.2;

    float d5 = distance(C5,vtexCoord);
    float d6 = distance(C6,vtexCoord);

    if (step(r5,d5) == 0 && step(r6,d6) != 0) {
    	float daux = distance(C1,vtexCoord);
    
    	float w = 0.1;
    	float f = smoothstep(r1-w,r1+w,d1);

    	fragColor = mix(ORANGE,BLACK,f);
    }

}

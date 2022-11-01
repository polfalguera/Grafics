#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

const vec4 red = vec4(1.0,0.0,0.0,1.0);
const vec4 white = vec4(1.0,1.0,1.0,1.0);

void main()
{
    vec2 C = vec2(0.5,0.5);
    float d = distance(vtexCoord,C);

    float w = length(vec2(dFdx(d),dFdy(d)));
    
    float f = smoothstep(0.2-w,0.2+w,d);

    //fragColor = mix(red,white,f);
     fragColor = vec4(1.0,vec3(f));
}

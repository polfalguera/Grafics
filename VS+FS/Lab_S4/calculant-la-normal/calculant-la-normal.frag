#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 VSvertex;

void main()
{

    vec3 v1 = dFdx(VSvertex);
    vec3 v2 = dFdy(VSvertex);

    vec3 normal = cross(v1,v2);
    normal = normalize(normal);

    fragColor = frontColor*normal.z;
}

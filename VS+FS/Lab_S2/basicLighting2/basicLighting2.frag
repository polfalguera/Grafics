#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 Nobject;

void main()
{
    vec3 N = normalize(Nobject);
    fragColor = frontColor * N.z;
}

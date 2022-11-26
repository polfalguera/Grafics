#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;

in vec3 N;
in vec3 P;

vec4 get_light (vec3 N, vec3 L, vec3 V)
{
    N = normalize(N);
    L = normalize(L);
    V = normalize(V);

    float NdotL = max(0.0,dot(N,L));

    vec4 ambient = matAmbient * lightAmbient;

    vec4 diffuse = matDiffuse * lightDiffuse * NdotL;

    vec4 specular = vec4(0.0);

    if (NdotL > 0.0) {
        vec3 R = 2 * (NdotL) * N-L;
        R = normalize(R);

        float RdotV = max(0.0,dot(R,V));

        specular = matSpecular * lightSpecular * pow(RdotV,matShininess);
    }

    return ambient+diffuse+specular;
}

void main()
{
    vec3 V = vec3(0,0,0)-P;
    vec3 L = lightPosition.xyz-P;
    fragColor = get_light(N,L,V);
}

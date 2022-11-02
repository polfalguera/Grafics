#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform mat4 viewMatrix;

in vec3 N;
in vec3 P;

vec4 get_light (vec3 N, vec3 L, vec3 V)
{
    L = normalize(L);

    float NdotL = max(0.0,dot(N,L));

    //vec4 ambient = matAmbient * lightAmbient;

    vec4 diffuse = matDiffuse * lightDiffuse * NdotL;

    vec4 specular = vec4(0.0);

    if (NdotL > 0.0) {
        vec3 R = 2 * (NdotL) * N-L;
        R = normalize(R);

        float RdotV = max(0.0,dot(R,V));

        specular = matSpecular * lightSpecular * pow(RdotV,matShininess);
    }

    return /*ambient+*/(diffuse / 2)+specular;
}

void main()
{
    // Llums en Eye Space
    vec3 lights[8];
    lights[0] = (viewMatrix * vec4(vec3(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMax.z),1.0)).xyz;
    lights[1] = (viewMatrix * vec4(vec3(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMin.z),1.0)).xyz;
    lights[2] = (viewMatrix * vec4(vec3(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMax.z),1.0)).xyz;
    lights[3] = (viewMatrix * vec4(vec3(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMin.z),1.0)).xyz;
    lights[4] = (viewMatrix * vec4(vec3(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMax.z),1.0)).xyz;
    lights[5] = (viewMatrix * vec4(vec3(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMin.z),1.0)).xyz;
    lights[6] = (viewMatrix * vec4(vec3(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMax.z),1.0)).xyz;
    lights[7] = (viewMatrix * vec4(vec3(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMin.z),1.0)).xyz;
    fragColor = vec4(0);

    vec3 V = -P;
    V = normalize(V);

    for(int i = 0; i < 8; ++i) {
        fragColor+=get_light(N,lights[i]-P,V);
    }
}

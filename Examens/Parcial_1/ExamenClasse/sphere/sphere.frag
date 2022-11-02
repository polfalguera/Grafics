#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform int mode=2;

const vec4 BLACK = vec4(vec3(0.0),1.0);
const vec4 WHITE = vec4(1.0);

uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

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
    vec2 C = vec2(0.0,0.0);
    float d = distance(vtexCoord,C);

    if (mode == 0) {
        float w = length(vec2(dFdx(d),dFdy(d)));
        float f = smoothstep(1.0-w,1.0+w,d);

        fragColor = mix(BLACK,WHITE,f);
    }
    else if (mode == 1) {
        if (step(1.0,d) == 0) {
            float s = vtexCoord.s;
            float t = vtexCoord.t;

            float aux = 1-pow(s,2)-pow(t,2);
            vec3 N = vec3(s,t,sqrt(aux));

            fragColor = vec4(vec3(N.z),1.0);
        }
        else discard;
    }
    else {
        if (step(1.0,d) == 0) {
            float s = vtexCoord.s;
            float t = vtexCoord.t;

            float aux = 1-pow(s,2)-pow(t,2);
            vec3 N = vec3(s,t,sqrt(aux));
            vec3 P = N;

            N = normalMatrix * N;
            P = vec4(modelViewMatrix * vec4(P,1.0)).xyz;

            vec3 V = vec3(0,0,0)-P;
            vec3 L = lightPosition.xyz-P;
            fragColor = get_light(N,L,V);
        }
        else discard;
    }
}



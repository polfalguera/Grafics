#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D noise_smooth;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

in vec3 N;
in vec3 V;

const vec4 planeS = 0.3 * vec4(0.0,1.0,-1.0,0.0);
const vec4 planeT = 0.3 * vec4(-2.0,-1.0,1.0,0.0);

const vec4 white  = vec4(1.0,1.0,1.0,1.0);
const vec4 redish = vec4(0.5,0.2,0.2,1.0);

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
 vec3 lightPos = vec3(0.0,0.0,2.0);
 vec3 L = normalize( lightPos - Pos );
 vec3 V = normalize( -Pos);
 vec3 R = reflect(-L,N);
 float NdotL = max( 0.0, dot( N,L ) );
 float RdotV = max( 0.0, dot( R,V ) );
 float Ispec = pow( RdotV, 20.0 );
 return diffuse * NdotL + Ispec;
}

void main()
{
    vec4 V4 = vec4(V,1.0);

    float s = dot(V4,planeS);
    float t = dot(V4,planeT);

    vec2 vtexCoord2=vec2(s, t);

    float v = texture(noise_smooth, vtexCoord2).x;

    vec4 diffuse = white;
    
    if (v < 0.5) diffuse = mix(white,redish,v*2); //??
    else diffuse = mix(redish,white,(v-0.5)*2); //??

    vec3 NE = normalize(normalMatrix*N);
    vec3 VE = normalize((modelViewMatrix*V4)).xyz;

    fragColor = shading(NE,VE,diffuse);
}

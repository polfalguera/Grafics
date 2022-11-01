#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

mat4 translateMatrix(float tx, float ty, float tz) {
    
    return mat4(vec4(1.0,0.0,0.0,0.0),
    		vec4(0.0,1.0,0.0,0.0),
    		vec4(0.0,0.0,1.0,0.0),
    		vec4(tx,ty,tz,1.0)
    		);
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);// * N.z;
    vtexCoord = texCoord;
    
    // Declaro l'angle de rotació A i la matriu de rotació.
    // La matriu haurà de ser de 4x4, ja que és el tamany de la matriu del translate.
    
    float A;
    
    if (vertex.y <= 0.5) A = 0.0;
    else A = (vertex.y-0.5)*sin(time);
    
    mat4 rotateMatrix = mat4(vec4(1.0,0.0,0.0,0.0),
    			     vec4(0.0,cos(A),sin(A),0.0),
    			     vec4(0.0,-sin(A),cos(A),0.0),
    			     vec4(0.0,0.0,0.0,1.0)
    		 	    );
    		 	    
    vec4 newVertex = translateMatrix(0.0,1.0,0.0) * rotateMatrix * translateMatrix(0.0,-1.0,0.0) * vec4(vertex,1.0);
    
    gl_Position = modelViewProjectionMatrix * newVertex;
}

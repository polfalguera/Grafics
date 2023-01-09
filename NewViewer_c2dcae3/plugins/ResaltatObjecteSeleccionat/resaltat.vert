#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main()
{
	frontColor = vec4(color,1.0);
	
	mat4 scale = mat4( // matriu d'escalat
		vec4(boundingBoxMax.x-boundingBoxMin.x, 0, 0, 0),   
		vec4(0, boundingBoxMax.y-boundingBoxMin.y, 0, 0),
		vec4(0, 0, boundingBoxMax.z-boundingBoxMin.z, 0),
		vec4(0, 0, 0, 1)
	);
  	vec4 C = vec4((boundingBoxMax+boundingBoxMin)/2, 0); // centre capsa contenidora
 	vec4 V = scale*vec4(vertex-vec3(0.5), 1);            // vertex escalat    
    gl_Position = modelViewProjectionMatrix*(V+C);		 // traslacio 
}

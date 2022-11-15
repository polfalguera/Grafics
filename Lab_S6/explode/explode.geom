#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
in vec3 vnormal[];

uniform mat4 modelViewProjectionMatrix;

const float speed = 0.5;
uniform float time;

void main( void )
{
	//Calculem el promig de les normals en OBJ space.
	vec3 n = (vnormal[0]+vnormal[1]+vnormal[2]) / 3.0;
	
	for( int i = 0 ; i < 3 ; i++)
	{
		gfrontColor = vfrontColor[i];
		//Translació.
		vec3 translate = speed * time * n;
		//Aplicació de la translació.
		vec4 P = gl_in[i].gl_Position;
		P += vec4(translate,0.0);
		//Passar el vèrtex traslladat a clip space.
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();
}

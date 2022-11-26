#version 330 core
        
layout(triangles) in; //tipo de primitiva
layout(triangle_strip, max_vertices = 36) out; //Indica com a màxim que emitirà 36 vèrtexs, 12 triangles.

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;

uniform vec3 boundingBoxMin;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position; //vertex del triangle en qüestió
		EmitVertex(); //Es genera un nou vèrtex amb les propietats anteriors que hem donat. 
	}
    	EndPrimitive();
    	
    	gfrontColor = vec4(0.0);
    	for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 P = gl_in[i].gl_Position;
		P.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    	EndPrimitive();
    	
    	
}

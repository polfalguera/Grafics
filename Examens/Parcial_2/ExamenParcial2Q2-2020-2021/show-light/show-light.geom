#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform vec4 lightPosition;
uniform float w = 0.3;

uniform mat4 projectionMatrix;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		gtexCoord = vec2(-1.0,-1.0);
		EmitVertex();
	}
    EndPrimitive();
    
    if(gl_PrimitiveIDIn == 0) {
    	vec4 C = projectionMatrix * lightPosition;
    	C /= C.w;
    	
    	gfrontColor = vec4(vec3(0.0),1.0);
    	
    	gl_Position = vec4(C.x+w,C.y+w,C.z,C.w);
    	gtexCoord = vec2(1.0,1.0);
    	EmitVertex();
    	
    	gl_Position = vec4(C.x+w,C.y-w,C.z,C.w);
    	gtexCoord = vec2(1.0,0.0);
    	EmitVertex();
    	
    	gl_Position = vec4(C.x-w,C.y+w,C.z,C.w);
    	gtexCoord = vec2(0.0,1.0);
    	EmitVertex();
    	
    	gl_Position = vec4(C.x-w,C.y-w,C.z,C.w);
    	gtexCoord = vec2(0.0,0.0);
    	EmitVertex();
    	
    	
    	EndPrimitive();
    	    	
    }
}

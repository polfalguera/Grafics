#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin, boundingBoxMax;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

const vec4 RED   = vec4(1.0,0.0,0.0,1.0);
const vec4 GREEN = vec4(0.0,1.0,0.0,1.0); 
const vec4 BLUE  = vec4(0.0,0.0,1.0,1.0); 

bool dins_capsa() {
	vec4 bbmin = modelViewMatrix * vec4(boundingBoxMin,1.0);
	vec4 bbmax = modelViewMatrix * vec4(boundingBoxMax,1.0);
	vec4 obs = vec4(0.0);
	
	return ((obs.x >= bbmin.x && obs.x <= bbmax.x) && (obs.y >= bbmin.y && obs.y <= bbmax.y) && (obs.z >= bbmin.z && obs.z <= bbmax.z));	
	
}

void main( void )
{
	
	for( int i = 0 ; i < 3 ; i++ )
	{
		if (dins_capsa()) gfrontColor = vfrontColor[i]*2;
		else gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    if (gl_PrimitiveIDIn == 0) {
    	vec3 bbmin = boundingBoxMin;
    	vec3 bbmax = boundingBoxMax;
    	
    	/* Cara verda */
    	gfrontColor = GREEN;
    	
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin.x,bbmin.y,bbmax.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax.x,bbmin.y,bbmin.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax.x,bbmin.y,bbmax.z,1.0);
    	EmitVertex();
    	
    	EndPrimitive();
    	
    	/* Cara blava */
    	gfrontColor = BLUE;
    	
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax.x,bbmin.y,bbmin.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin.x,bbmax.y,bbmin.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax.x,bbmax.y,bbmin.z,1.0);
    	EmitVertex();
    	
    	EndPrimitive();
    	
    	/* Cares vermelles */
    	gfrontColor = RED;
    	
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin.x,bbmin.y,bbmax.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin.x,bbmax.y,bbmin.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmin.x,bbmax.y,bbmax.z,1.0);
    	EmitVertex();
    	
    	EndPrimitive();
    	
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax.x,bbmin.y,bbmax.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax.x,bbmax.y,bbmin.z,1.0);
    	EmitVertex();
    	gl_Position = modelViewProjectionMatrix * vec4(bbmax.x,bbmin.y,bbmin.z,1.0);
    	EmitVertex();
    	
    	EndPrimitive();
    }
}

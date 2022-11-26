#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

in vec2 vtexCoord[];
out vec2 gtexCoord;

uniform mat4 modelViewProjectionMatrix;

uniform float step = 0.2;

out float caraSuperior;

vec4 calcularBaricentre() {
	vec4 V1 = gl_in[0].gl_Position;
	vec4 V2 = gl_in[1].gl_Position;
	vec4 V3 = gl_in[2].gl_Position;

	return (V1+V2+V3) / 3.0;
}

void pintarCaraCub(vec4 V1, vec4 V2, vec4 V3, vec4 V4) {
	caraSuperior = 0;
	
	gfrontColor = vfrontColor[0];

	
	gl_Position = modelViewProjectionMatrix*V1; 
	EmitVertex();
    gl_Position = modelViewProjectionMatrix*V2; 
	EmitVertex();
    gl_Position = modelViewProjectionMatrix*V3; 
	EmitVertex();
    gl_Position = modelViewProjectionMatrix*V4; 
	EmitVertex();
    
	EndPrimitive();
}

void pintarCaraSuperior(vec4 V1, vec4 V2, vec4 V3, vec4 V4) {
	caraSuperior = 1;
	
	gfrontColor = vfrontColor[0];

	gtexCoord = vec2(0,0);
	gl_Position = modelViewProjectionMatrix*V1; 
	EmitVertex();
	gtexCoord = vec2(1,0);
    gl_Position = modelViewProjectionMatrix*V2; 
	EmitVertex();
	gtexCoord = vec2(0,1);
    gl_Position = modelViewProjectionMatrix*V3; 
	EmitVertex();
	gtexCoord = vec2(1,1);
    gl_Position = modelViewProjectionMatrix*V4; 
	EmitVertex();
    
	EndPrimitive();
}

vec4 calcularV(vec4 C, float Rx, float Ry, float Rz) {
	return C+vec4(Rx,Ry,Rz,0.0);
}

void main( void )
{
	vec4 bar = calcularBaricentre();
	vec4 C = round(bar / step) * step;
	float R = step / 2; 
	
	//Cara frontal
	pintarCaraCub(calcularV(C,-R,-R,R),calcularV(C,-R,R,R),calcularV(C,R,-R,R),calcularV(C,R,R,R));
	//Cara dorsal
	pintarCaraCub(calcularV(C,R,R,-R),calcularV(C,R,-R,-R),calcularV(C,-R,R,-R),calcularV(C,-R,-R,-R));
	//Cara superior
	pintarCaraSuperior(calcularV(C,-R,R,R),calcularV(C,R,R,R),calcularV(C,-R,R,-R),calcularV(C,R,R,-R));
	//Cara inferior
	pintarCaraCub(calcularV(C,R,-R,-R),calcularV(C,-R,-R,-R),calcularV(C,R,-R,R),calcularV(C,-R,-R,R));
	//Cara lateral dret
	pintarCaraCub(calcularV(C,R,R,R),calcularV(C,R,-R,R),calcularV(C,R,R,-R),calcularV(C,R,-R,-R));
	//Cara lateral esquerre
	pintarCaraCub(calcularV(C,-R,-R,-R),calcularV(C,-R,R,-R),calcularV(C,-R,-R,R),calcularV(C,-R,R,R));		
}
#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2  vtexCoord;
in vec3 N;

uniform float time;
uniform sampler2D window;
uniform sampler2D palm1;
uniform sampler2D background2;

void main()
{
	vec4 C = texture(window,vtexCoord);
	if (C.w == 1.0) fragColor = C;
	else if (C.w < 1.0) {
		vec4 D = texture(palm1,vtexCoord + 0.25*N.xy + vec2(0.1*sin(2*time)*vtexCoord.t, 0));
		if (D.w >= 0.5) fragColor = D;
		else fragColor = texture(background2,vtexCoord + 0.5*N.xy);
	}
}

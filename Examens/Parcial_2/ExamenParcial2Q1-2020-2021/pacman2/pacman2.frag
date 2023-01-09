#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D colormap;

const float div = 1.0/6.0; // Perquè tenim 6 elements

bool esEsquina(int x, int y) {
	return (x == 0 && y == 0) || (x == 12 && y == 0) || (x == 0 && y == 12) || (x == 12 && y == 12);
}

void main()
{
	// Passant del rang [0..1] a [0..13]
	int Qx = int(vtexCoord.s * 13.0);
	int Qy = int(vtexCoord.t * 13.0);
	float x,y,offset;
	x = fract(vtexCoord.s*13.0);
	y = fract(vtexCoord.t*13.0);
	vec2 coords;
	if (esEsquina(Qx, Qy)) {
        if (Qx == 0 && Qy == 0) {
            x = 1 - x;
            y = 1 - y/6.0;
            // Escollim quin del 6 elements volem dibuixar
            offset = 5.0/6.0;
            coords = vec2(y+offset, x);
        }
        else if (Qx == 0 && Qy == 12) {
            x = -x/6.0;
            y = y;
            // Escollim quin del 6 elements volem dibuixar
            offset = 5.0/6.0;
            coords = vec2(x+offset, y);
        }
        else if (Qx == 12 && Qy == 0) {
            x = x/6.0;
            y = 1 - y;
            // Escollim quin del 6 elements volem dibuixar
            offset = 4.0/6.0;
            coords = vec2(x+offset, y);
        }
        else if (Qx == 12 && Qy == 12) {
            // Hem de dividir la textura pacman.png en 6 trossos, ja que hi ha 6 
            // elements diferents per dibuixar. En aquest cas ho fem en les s perque
            // interpretem la textura en horitzontal
            x = x/6.0;
            // Escollim quin del 6 elements volem dibuixar
            offset = 4.0/6.0;
            coords = vec2(x+offset, y);
        }
        fragColor = texture(colormap, coords);
    }
    else if (Qx == 0 || Qx == 12) {
    	x = x;
    	y = y/6.0;
    	offset = 3.0/6.0;
    	coords = vec2(y+offset,x);
    	fragColor = texture(colormap,coords);
    }
    else if (Qy == 0 || Qy == 12) {
    	x = x/6.0;
    	y = y;
    	offset = 3.0/6.0;
    	coords = vec2(x+offset,y);
    	fragColor = texture(colormap,coords);
    }
    else if (((Qx >= 2 && Qx <= 5) || (Qx >= 7 && Qx <= 10)) && (Qy == 2 || Qy == 4 || Qy == 6 || Qy == 8 || Qy == 10)) {
    	x = x/6.0;
    	y = y;
    	offset = 3.0/6.0;
    	coords = vec2(x+offset,y);
    	fragColor = texture(colormap,coords);
    }
    else if ((Qx >= 7 && Qx <= 10) && Qy == 3) fragColor = vec4(0.0);
    else if ((Qx == 1 || Qx ==5) && Qy == 3) {
    	x = x/6.0;
    	y = y;
    	offset = 0.0/6.0;
    	coords = vec2(x+offset,y);
    	fragColor = texture(colormap,coords);
    }
    else if (Qx == 4 && Qy == 3) {
    	x = x/6.0;
    	y = y;
    	offset = 1.0/6.0;
    	coords = vec2(x+offset,y);
    	fragColor = texture(colormap,coords);
    }
    else {
    	x = x/6.0;
    	y = y;
    	offset = 5.0/6.0;
    	coords = vec2(x+offset,y);
    	fragColor = texture(colormap,coords);
    }
}

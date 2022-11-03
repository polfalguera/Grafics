
/*NO ESTÀ DEL TOT BÉ. LA DISPOSICIÓ DELS OBJECTES POT SER MILLOR*/
/*EL MÉS IMPORTANT QUE FALLA ÉS COM PILLAR LES TEXTURES, ME LES FA AXATADES*/

#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;
uniform sampler2D colormap;

float div = 1.0 / 7.0;

/*void pintarTerra() {   
    // Objecte que vui agafar de la textura
    float obj = 2 * div;
    // Quina porció de la part de la textura li pertoca a vtexCoord.s
    float offset = mod(vtexCoord.s,div);

    //vtexCoord.t la multiplico * 13 per que la textura es repeteixi 13 cops

    fragColor = texture(colormap,vec2(obj+offset, vtexCoord.t*13));
}*/

void pintar(float f) {
    float obj = f * div;
    float offset = mod(vtexCoord.s,div);

    fragColor = texture(colormap,vec2(obj+offset, vtexCoord.t*13));
}

void main()
{
    float x = vtexCoord.s*13;
    float y = vtexCoord.t*13;

    if (y > 0 && y < 1 || y > 3 && y < 4 || y > 6 && y < 7 || y > 9 && y < 10 || y > 11 && y < 12 && x > div*1*13 && x < div*4*13) pintar(2);
    else if (x > 1*div*13 && x < 2*div*13 && y > 7 && y < 8) pintar(5);
    else if (x > 6*div*13 && x < 7*div*13 && y > 10 && y < 11) pintar(1);
    else if (x > 2*div*13 && x < 3*div*13 && y > 12 && y < 13) pintar(4);
    else if (y < 4 && y < 5  || y >=5 && y <= 6 ) pintar(3);
    else if (x > 4*div*13 && x < 6*div*13 && (y > 9 && y < 10 || y > 10 && y < 12)) pintar(0);
    else if (y > 4 && y < 5) pintar(0);
    else fragColor = vec4(0.0); 
}

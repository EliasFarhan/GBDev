#include <gb/gb.h>
#include <rand.h>
#include "sprites.c"
#include "background.c"
#include "sonido.c"
#include "portadamap.c"
#include "portada.c"

#define num_nubes 4					//No poner demasiadas, debemos recordar que tenemos un maximo de 40 sprites
#define potencia_salto 20
#define gravedad 4					//mayor numero -> menor gravedad
#define x_inicial 40				//Posicion horizontal del dinosaurio
#define y_inicial 112				//Posicion vertical en el suelo del dinosaurio

#define tamano_mapa 300
const UBYTE mapa[]= {
0,0,0,0,0,0,0,1,1,0,
0,0,1,1,0,0,0,0,1,0,
0,0,0,0,0,1,0,0,0,0,
1,1,0,0,0,0,1,0,0,0,
0,1,1,0,0,0,0,0,1,1,
0,0,0,0,0,0,2,3,0,0,
0,0,1,0,0,0,0,0,2,3,
0,0,0,0,1,0,0,0,0,0,
1,1,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,0,1,1,0,
0,0,0,0,1,0,0,0,0,1,
0,0,0,0,1,0,0,0,0,0,
0,2,3,0,0,0,0,1,1,0,
0,0,0,0,1,0,0,0,0,0,
0,0,0,1,1,0,0,0,0,1,
0,0,0,0,0,1,1,0,0,0,
0,0,1,0,0,0,0,0,1,1,
0,0,0,0,0,0,0,2,3,2,
3,0,0,0,0,0,1,1,0,0,
0,0,2,3,2,3,0,0,0,1,
0,0,0,0,0,1,0,0,0,0,
1,1,0,0,0,0,1,0,0,0,
0,1,1,0,0,0,0,0,1,1,
0,0,0,0,0,0,2,3,0,0,
0,0,1,0,0,0,0,0,2,3,
0,0,0,0,1,0,0,0,0,0,
1,1,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,0,1,1,0,
0,0,0,0,0,0,2,3,0,0,
0,0,0,1,1,0,0,0,0,1
};

UWORD highscores[]= {200,150,100,50,25};

void inicializa_sprites() 
{
	UBYTE i,x,y;
	SPRITES_8x16;					//INICIALIZACION
	set_sprite_data(0,36,Sprites);
	set_sprite_tile(0,0);			//Tile del dinosaurio que no cambia en todo el juego REUTILIZABLE!!

	
	for (i=0;i<num_nubes;i++)		//establecemos y colocamos nubes
	{
		x=rand()/2;
		y=rand()/2;
		set_sprite_tile(7+i*4,22);
		set_sprite_tile(8+i*4,24);
		set_sprite_tile(9+i*4,26);
		set_sprite_tile(10+i*4,28);
		move_sprite(7+i*4,x,y);
		move_sprite(8+i*4,x+8,y);
		move_sprite(9+i*4,x+16,y);
		move_sprite(10+i*4,x+24,y);
	}
}

void mueve_nubes() 
{
	UBYTE i;
	for (i=7;i<(11+(num_nubes-1)*4);i++) scroll_sprite(i,-1,0);
}


UBYTE pulsa_boton()
{
	UBYTE key=joypad();
	if ( key & J_A) return 1;
	if ( key & J_B) return 1;
	if ( key & J_DOWN) return 2;
	return 0;
}

void anima_dinosaurio(UBYTE anim)
{
	if (anim==4)			//La animacion de agachado es muy distinta a las demas
	{
		set_sprite_tile(1,0);
		set_sprite_tile(2,0);
		set_sprite_tile(3,6);
		set_sprite_tile(4,30);
		set_sprite_tile(5,32);
		set_sprite_tile(6,34);
		return;
	}
	else
	{
		set_sprite_tile(5,10);
		set_sprite_tile(6,0);
	}
	
	if (anim==3)					//CONTROLAMOS CARA DINOSAURIO
		{
			set_sprite_tile(1,18);	//muerto
			set_sprite_tile(2,20);
		}
		else
		{
			set_sprite_tile(1,2);	//vivo
			set_sprite_tile(2,4);
		}
		
	switch (anim)					//CONTROLAMOS PATAS DINOSAURIO
	{
		case 0:							//pata derecha levantada
		set_sprite_tile(3,6);
		set_sprite_tile(4,12);
		break;
		case 1:							//pata izquierda levantada
		set_sprite_tile(3,14);
		set_sprite_tile(4,16);
		break;
		default:						//parado, saltando, o muerto
		set_sprite_tile(3,6);
		set_sprite_tile(4,8);
		break;
	}
	
}

void mueve_dinosaurio(BYTE x, BYTE y)
{
	move_sprite(0,x,y);
	move_sprite(1,x+8,y);
	move_sprite(2,x+16,y);
	move_sprite(3,x,y+16);
	move_sprite(4,x+8,y+16);
	move_sprite(5,x+16,y+16);
	move_sprite(6,x+24,y+16);
}


void pantalla_inicio()
{
	HIDE_SPRITES;
	//printf("@Juanmv94\n@Alejandro D.");			//Autoría del Juego
	set_bkg_data( 0, 134, TileData); 			//Tiles pantalla inicio
	set_bkg_tiles( 0, 0, 20, 18, Tilemap);			//Mapa de tiles pantalla inicio
	while(pulsa_boton()==0) {wait_vbl_done();}		//Esperamos que se pulse tecla
	while(pulsa_boton()==1) {wait_vbl_done();}		//Esperamos que se suelte tecla
}

void dibuja_background_libre(UBYTE posicion) {
	set_bkg_tiles(posicion*2, 0, 2, 16, cielo);				//Pone background en blanco, puede haber un obstaculo o pantalla inicio
	set_bkg_tiles(posicion*2, 16, 2, 1, suelos[rand()/32]);		//Dibuja suelo aleatorio
}

void dibuja_obstaculo(UBYTE posicion) {
	set_bkg_tiles(posicion*2,13,2,4,obstaculo);	
}

void dibuja_terodactilo_cabeza(UBYTE posicion) {
	set_bkg_tiles(posicion*2,13,2,2,terodactilo_cabeza);
	set_bkg_tiles(posicion*2+1,15,2,1,cielo);
	set_bkg_tiles(posicion*2, 16, 2, 1, suelos[rand()/32]);		//Dibuja suelo aleatorio
}

void dibuja_terodactilo_cola(UBYTE posicion) {
	set_bkg_tiles(posicion*2,13,1,2,terodactilo_cola);
	set_bkg_tiles(posicion*2+1,13,1,2,cielo);
	set_bkg_tiles(posicion*2+1,15,2,1,cielo);
	set_bkg_tiles(posicion*2, 16, 2, 1, suelos[rand()/32]);		//Dibuja suelo aleatorio
}

void dibuja_elemento(UBYTE elemento, UBYTE pos)
{
	switch (elemento)
	{
		case 1:
		dibuja_obstaculo(pos);
		break;
		case 2:
		dibuja_terodactilo_cabeza(pos);
		break;
		case 3:
		dibuja_terodactilo_cola(pos);
		break;
		default:
		dibuja_background_libre(pos);
		break;		
	}
}

void background_inicial() 
	{
		UBYTE i;
		for (i=0;i<16;i++) {
		dibuja_background_libre(i);
		}
		for (i=0;i<10;i++) {
		dibuja_elemento(mapa[i],i);
		}
	}

void imprime_numero(UWORD numero, BYTE x, BYTE y)
{
	UWORD num=numero;
	UWORD n[5];
	n[0]=num/10000;
	num-=n[0]*10000;
	n[1]=num/1000;
	num-=n[1]*1000;
	n[2]=num/100;
	num-=n[2]*100;
	n[3]=num/10;
	num-=n[3]*10;
	n[4]=num;

	for (num=0;num<5;num++)
	{
		set_win_tiles(x+num,y,1,1,numeros[n[num]]);
	}
}
	
void sube_puntuacion(UWORD p)
{
	UBYTE i=0,ii;
	WORD tmp=highscores[0]-p;
	while (tmp>0)
	{
		i++;
		if (i==5) return;
		tmp=highscores[i]-p;
	}
	for (ii=4;ii>i;ii--)
	{
		highscores[ii]=highscores[ii-1];
	}
	highscores[i]=p;
}
	
void juego_main()
{
	UBYTE timer=0,pata=0,posicionbk=0,key;
	BYTE velocidad;
	WORD altura=1;									//necesitamos 16 bit para tener numeros >254
	UWORD puntuacion=0,posicionmap=0;
	set_bkg_data(0,12,Background);
	move_bkg(-15-x_inicial,0);
	background_inicial();	
	anima_dinosaurio(2);
	mueve_dinosaurio(x_inicial,y_inicial);
	SHOW_SPRITES;
	set_win_tiles(1,0,2,1,hi);
	imprime_numero(highscores[0],4,0);
	SHOW_WIN;
	scroll_win(0,136);
	while(pulsa_boton()==0) {wait_vbl_done();}		//Esperamos que se pulse tecla
	sonido_salto();
	velocidad=potencia_salto;
	while(get_sprite_tile(1)!=18)					//mientras este vivo
	{
		if (altura<0) {altura=0; mueve_dinosaurio(x_inicial,y_inicial);}	//cuando cae debemos evitar que atraviese el suelo
		if (altura==0)								//CODIGO EN EL SUELO
		{
			key=pulsa_boton();
			if (key==1) {sonido_salto(); altura=1; velocidad=potencia_salto;}		//si se pulsa boton, salta
			else if (key==2) {														//si se pulsa boton agachar
			anima_dinosaurio(4);
			if (mapa[posicionmap]==1) {anima_dinosaurio(3); sonido_muerte();}		//no evitamos cactus
			}
			else if (mapa[posicionmap]>0) {anima_dinosaurio(3); sonido_muerte();}	//si no, y si hay un obstaculo muere
			else if (timer==0) 												//si no hay obstaculo, anima normalmente
				{
					anima_dinosaurio(pata);
				}
		}
		else										//CODIGO EN EL AIRE
		{
		if (mapa[posicionmap]>0)	puntuacion++;							//aumentamos puntos
		anima_dinosaurio(2);
		mueve_dinosaurio(x_inicial,y_inicial-altura/gravedad);
		altura+=velocidad;
		velocidad--;
		}
		
		if (timer<7) timer++;						//CODIGO RELACIONADO CON TIMER, GENERACION DE BK Y MAPA
		else {timer=0;								//cada 16 pixeles pasamos a la siguiente posicion
			pata= (pata+1)%2;						//animacion: si pata=1, entonces pata=0 y viceversa
			set_bkg_data(12,6,Tero[pata]);
			imprime_numero(puntuacion,12,0);
			posicionbk++;
			posicionmap++;
			if (posicionbk>15) posicionbk=0;		//el background tiene 32 tiles de ancho, que son 16 posiciones de 2 tiles
			if (posicionmap==tamano_mapa) posicionmap=0;	//El mapa se repite en bucle
			
			dibuja_elemento(mapa[(posicionmap+8)%tamano_mapa],(posicionbk+8)%16);	//Dibujamos nuevo elemento
		}
		
		scroll_bkg(2,0);									//hacemos scroll horizontal del background, 2px cada frame
		mueve_nubes(); 										//scroll horizontal de las nubes
		wait_vbl_done();									//Generamos frame
	}
	
	while(pulsa_boton()!=1) {wait_vbl_done();}		//Esperamos que se pulse tecla
	while(pulsa_boton()!=0) {wait_vbl_done();}		//Esperamos que se suelte tecla
	HIDE_WIN;
	scroll_win(0,-136);								//dejamos la ventana como estaba
	
	sube_puntuacion(puntuacion);

}

void pantalla_puntuaciones()
{
	UBYTE punt;
	HIDE_SPRITES;
	set_win_tiles(5,3,9,1,gameover);
	for (punt=0;punt<5;punt++) {
		imprime_numero(highscores[punt],7,5+punt);
	}
	set_win_tiles(5,11,9,1,tryagain);
	set_win_tiles(0,16,6,1,juanm);
	set_win_tiles(0,17,20,1,alexd);
	

	SHOW_WIN;


	while(pulsa_boton()==0) {wait_vbl_done();}		//Esperamos que se pulse tecla
	while(pulsa_boton()==1) {wait_vbl_done();}		//Esperamos que se suelte tecla
}

void main()
{	
	SHOW_BKG;
	initrand(9);
	inicializa_sprites();
	pantalla_inicio();
	while (1==1) 
	{
		juego_main();
		pantalla_puntuaciones();
	}
}



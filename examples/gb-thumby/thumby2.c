#include <gb/gb.h>

/*
 * Thumby2 is a Pong Clone written by Belial
 * Control the left paddle with the game pad
 * The right paddle is controlled by the CPU
 * Game is begins after pressing START button
 * Game restarts after a player scores the 10th time
 *
 */

unsigned char backgroundcharacters[] = {
	//ecke oben links
	0xFF,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	//ecke oben rechts
	0xFF,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	//ecke unten links
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0xFF,0xFF,0xFF,0xFF,
	//ecke unten rechts
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0xFF,0xFF,0xFF,0xFF,
	//wand oben
	0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	//wand rechts
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	//wand unten
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
	//wand links
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	//leer
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
}; 

signed char spritetiles[] = 
{
	//paddle
	255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,
	//ball
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	//null
	0x00,0x00,0x18,0x18,0x24,0x24,0x24,0x24,
	0x24,0x24,0x24,0x24,0x18,0x18,0x00,0x00,
	//eins
	0x00,0x00,0x08,0x08,0x18,0x18,0x28,0x28,
	0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
	//zwei
	0x00,0x00,0x18,0x18,0x24,0x24,0x08,0x08,
	0x10,0x10,0x20,0x20,0x3C,0x3C,0x00,0x00,
	//drei
	0x38,0x38,0x04,0x04,0x04,0x04,0x38,0x38,
	0x04,0x04,0x04,0x04,0x38,0x38,0x00,0x00,
	//vier
	0x08,0x08,0x10,0x10,0x20,0x20,0x48,0x48,
	0x7C,0x7C,0x08,0x08,0x08,0x08,0x00,0x00,
	//fuenf
	0x00,0x00,0x3C,0x3C,0x20,0x20,0x38,0x38,
	0x04,0x04,0x04,0x04,0x38,0x38,0x00,0x00,
	//sechs
	0x00,0x00,0x1C,0x1C,0x20,0x20,0x20,0x20,
	0x3C,0x3C,0x24,0x24,0x3C,0x3C,0x00,0x00,
	//sieben
	0x00,0x00,0x3C,0x3C,0x04,0x04,0x08,0x08,
	0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	//acht
	0x18,0x18,0x24,0x24,0x24,0x24,0x18,0x18,
	0x24,0x24,0x24,0x24,0x18,0x18,0x00,0x00,
	//neun
	0x18,0x18,0x24,0x24,0x24,0x24,0x1C,0x1C,
	0x04,0x04,0x04,0x04,0x18,0x18,0x00,0x00,
	//zehn
	0x26,0x26,0x69,0x69,0xA9,0xA9,0x29,0x29,
	0x29,0x29,0x29,0x29,0x26,0x26,0x00,0x00
};

signed char collision_left_up[] = 
{
	3,-1,1,0,
	3,-1,1,0,
	3,-1,1,0,
	3,-1,1,0,
	//--
	3,-1,2,-1,
	3,-1,2,-1,
	3,-1,2,-1,
	3,-1,2,-1,
	//--
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1,
	//--
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1,
	3,-2,2,-1
};

signed char collision_left_down[] = 
{
	3,1,1,0,
	3,1,1,0,
	3,1,1,0,
	3,1,1,0,
	//--
	3,1,2,1,
	3,1,2,1,
	3,1,2,1,
	3,1,2,1,
	//--
	3,2,2,1,
	3,2,2,1,
	3,2,2,1,
	3,2,2,1,
	//--
	3,2,3,1,
	3,2,3,1,
	3,2,3,1,
	3,2,3,1
};

signed char collision_right_up[] = 
{
	-3,-1,-1,0,
	-3,-1,-1,0,
	-3,-1,-1,0,
	-3,-1,-1,0,
	//--
	-3,-1,-2,-1,
	-3,-1,-2,-1,
	-3,-1,-2,-1,
	-3,-1,-2,-1,
	//--
	-3,-2,-2,-1,
	-3,-2,-2,-1,
	-3,-2,-2,-1,
	-3,-2,-2,-1,
	//--
	-3,-2,-3,-1,
	-3,-2,-3,-1,
	-3,-2,-3,-1,
	-3,-2,-3,-1
};

signed char collision_right_down[] =
{
	-3,1,-1,0,
	-3,1,-1,0,
	-3,1,-1,0,
	-3,1,-1,0,
	//--
	-3,1,-2,1,
	-3,1,-2,1,
	-3,1,-2,1,
	-3,1,-2,1,
	//--
	-3,2,-2,1,
	-3,2,-2,1,
	-3,2,-2,1,
	-3,2,-2,1,
	//--
	-3,2,-3,1,
	-3,2,-3,1,
	-3,2,-3,1,
	-3,2,-3,1
};
	
signed char bgmap[] = {
	//oben
	0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1,
	//mitte
	7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,5,
	//unten
	2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,
	//nüscht
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};

//globale variablen
UBYTE counter,y1,y2,y3,y4,y5,y6;
UBYTE ball_pos_x;
UBYTE ball_pos_y;
BYTE ball_vektor_x1;
BYTE ball_vektor_x2;
BYTE ball_vektor_y1;
BYTE ball_vektor_y2;
UBYTE vektor_pointer;
UBYTE game_status;
UBYTE colx;
UBYTE coly;
BYTE temp1;
BYTE temp2;
UBYTE col0;
UBYTE col1;
BYTE* col_table;
BYTE score_p1;
BYTE score_p2;

//funktiondeklarationen
void resetKoords();
UBYTE checkCollisionBallPaddle(UBYTE paddleNr);

//funktionen
void resetKoords(){
	//pos paddle 0
	y1=65;
	y2=73;
	y3=81;
	//pos paddle 1
	y4=65;
	y5=73;
	y6=81;
	//pos ball
	ball_pos_x=80;
	ball_pos_y=77;
	//initialize moving vektor
	ball_vektor_x1=0;
	ball_vektor_x2=0;
	ball_vektor_y1=0;
	ball_vektor_y2=0;
	vektor_pointer=0;
	
	//set game to pause
	game_status=0;
	return;
}

UBYTE checkCollisionBallPaddle(UBYTE paddleNr){
	//P0
	if(paddleNr==0){
		if(ball_pos_x>=15) 
			colx = ball_pos_x - 15;	
		else 
			colx = 15 - ball_pos_x;
		if (colx<8){
			//from x point of view there might be a collision
			if (ball_pos_y >= y2) coly = ball_pos_y - y2;
			else coly = y2 - ball_pos_y;
			//check the y point of view
			return coly;
		}
		return 16;
	}
	//P1
	else{
		
		if(ball_pos_x>=153) 
			colx = ball_pos_x - 153;	
		else 
			colx = 153 - ball_pos_x;
		if (colx<8){
			//from x point of view there might be a collision
			if (ball_pos_y >= y5) coly = ball_pos_y - y5;
			else coly = y5 - ball_pos_y;
			//check the y point of view
			return coly;
		}
		return 16;
	}
}

main(){
	disable_interrupts();
	DISPLAY_OFF;
	
	resetKoords();
	
	//set score to 0
	score_p1=0;
	score_p2=0;

	//background
	set_bkg_data(0,10,backgroundcharacters);
	//background oben
	set_bkg_tiles(0, 0, 20, 1, bgmap);
	//background mitte
	for(counter=1;counter<=13;counter++) set_bkg_tiles(0,counter,20,1,bgmap+20);
	//background unten
	set_bkg_tiles(0,14,20,1,bgmap+40);
	//leer für score etc
	for(counter=15;counter<=17;counter++) set_bkg_tiles(0,counter,20,1,bgmap+20);
	set_bkg_tiles(0,14,20,1,bgmap+40);
	
	//load sprite
	SPRITES_8x8;
	//load paddle tile
	set_sprite_data(0, 1, spritetiles);
	//load ball tile
	set_sprite_data(1, 1, spritetiles+16);
	//load score
	set_sprite_data(2, 1, spritetiles+32);
	set_sprite_data(3, 1, spritetiles+48);
	set_sprite_data(4, 1, spritetiles+64);
	set_sprite_data(5, 1, spritetiles+80);
	set_sprite_data(6, 1, spritetiles+96);
	set_sprite_data(7, 1, spritetiles+112);
	set_sprite_data(8, 1, spritetiles+128);
	set_sprite_data(9, 1, spritetiles+144);
	set_sprite_data(10, 1, spritetiles+160);
	set_sprite_data(11, 1, spritetiles+176);
	set_sprite_data(12, 1, spritetiles+192);
	
	//paddle 0
	set_sprite_tile(0,0);
	set_sprite_tile(1,0);
	set_sprite_tile(2,0);
	//paddle 1
	set_sprite_tile(3,0);
	set_sprite_tile(4,0);
	set_sprite_tile(5,0);
	//ball
	set_sprite_tile(6,1);
	
	//aktiviere bildschirm
	SHOW_BKG;
	SHOW_SPRITES; 
	DISPLAY_ON;
	enable_interrupts();
	
	while(1) {
	/* Skip four VBLs (slow down animation) */
		//for(counter = 0; counter < 10; counter++){ //64
			wait_vbl_done();
		//}
		counter = joypad();
		
		//set score score
		set_sprite_tile(7,2+score_p1);
		set_sprite_tile(8,2+score_p2);

		//check paddle 0 for move
		if(counter & J_UP && y1>=20){
			y1-=1;
			y2-=1;
			y3-=1;
			if(checkCollisionBallPaddle(0)<16){
				y1+=1;
				y2+=1;
				y3+=1;
			}
		}
		if(counter & J_DOWN && y3<=124){
			y1+=1;
			y2+=1;
			y3+=1;
			if(checkCollisionBallPaddle(0)<16){
				y1-=1;
				y2-=1;
				y3-=1;
			}
		}

		//check paddle 1 for move
		if(y5 > ball_pos_y && y4 >= 20){
			y4-=1;
			y5-=1;
			y6-=1;
			if(checkCollisionBallPaddle(1)<16){
				y4+=1;
				y5+=1;
				y6+=1;
			}
		}
		if(y5 < ball_pos_y && y6 <= 124){
			y4+=1;
			y5+=1;
			y6+=1;
			if(checkCollisionBallPaddle(1)<16){
				y4-=1;
				y5-=1;
				y6-=1;
			}
		}

		//start game?
		if(counter & J_START && game_status==0){
			//if gameover, reset score
			if(score_p1==10 || score_p2==10){
				score_p1=0;
				score_p2=0;
			}
			ball_vektor_x1=1;
			ball_vektor_x2=1;
			ball_vektor_y1=1;
			ball_vektor_y2=1;
			game_status=1; //game is now running
		}
		
		//move ball
		if(vektor_pointer==0){
			temp1=ball_vektor_x1;
			temp2=ball_vektor_y1;
			vektor_pointer=1;
		}
		else{
			temp1=ball_vektor_x2;
			temp2=ball_vektor_y2;
			vektor_pointer=0;
		}
		ball_pos_x+=temp1;
		ball_pos_y+=temp2;
		col0=checkCollisionBallPaddle(0);
		if(col0<16){
			while(temp1!=0 || temp2!=0){
				if(temp1>0){
					temp1--;
					ball_pos_x--;
				}
				if(temp1<0){
					temp1++;
					ball_pos_x++;
				}
				if(temp2>0){
					temp2--;
					ball_pos_y--;
				}
				if(temp2<0){
					temp2++;
					ball_pos_y++;
				}
				if (checkCollisionBallPaddle(0)>=16) break;
			}
		}
		col1=checkCollisionBallPaddle(1);
		if (col1<16){
			while(temp1!=0 || temp2!=0){
				if(temp1>0){
					temp1--;
					ball_pos_x--;
				}
				if(temp1<0){
					temp1++;
					ball_pos_x++;
				}
				if(temp2>0){
					temp2--;
					ball_pos_y--;
				}
				if(temp2<0){
					temp2++;
					ball_pos_y++;
				}
				if (checkCollisionBallPaddle(1)>=16) break;
			}
		}

		//collision detection
		//left wall
		if(ball_pos_x<9){
			resetKoords();
			score_p2++;
		}
		//right wall
		if(ball_pos_x>163){
			resetKoords();
			score_p1++;
		}
		//upper wall
		if(ball_pos_y<19){
			ball_pos_y=19;
			ball_vektor_y1--;
			ball_vektor_y1=ball_vektor_y1 ^ 255;
			ball_vektor_y2--;
			ball_vektor_y2=ball_vektor_y2 ^ 255;
		}
		//lower wall
		if(ball_pos_y>125){
			ball_pos_y=125;
			ball_vektor_y1--;
			ball_vektor_y1=ball_vektor_y1 ^ 255;
			ball_vektor_y2--;
			ball_vektor_y2=ball_vektor_y2 ^ 255;
		}
		
		//col0
		if(col0<16 && ball_pos_x==23){
			//ball moves up
			if(ball_vektor_y1<0 || ball_vektor_y2<0) col_table = &collision_left_up;
			//ball moves down
			else col_table = &collision_left_down;
			col_table+=col0*4;
			ball_vektor_x1 = *col_table;
			ball_vektor_y1 = *(col_table+1);
			ball_vektor_x2 = *(col_table+2);
			ball_vektor_y2 = *(col_table+3);
		}

		//col1
		if(col1<16 && ball_pos_x==145){
			//ball moves up
			if(ball_vektor_y1<0 || ball_vektor_y2<0) col_table = &collision_right_up;
			//ball moves down
			else col_table = &collision_right_down;
			col_table+=col1*4;
			ball_vektor_x1 = *col_table;
			ball_vektor_y1 = *(col_table+1);
			ball_vektor_x2 = *(col_table+2);
			ball_vektor_y2 = *(col_table+3);
		}

		//sonderfall col0
		if(col0<16 && ball_pos_x!=23){
			ball_vektor_y1--;
			ball_vektor_y2--;
			ball_vektor_y1=ball_vektor_y1^255;
			ball_vektor_y2=ball_vektor_y2^255;
		}

		//sonderfall col1
		if(col1<16 && ball_pos_x!=145){
			ball_vektor_y1--;
			ball_vektor_y2--;
			ball_vektor_y1=ball_vektor_y1^255;
			ball_vektor_y2=ball_vektor_y2^255;
		}

		//paint p0
		move_sprite(0,15,y1);
		move_sprite(1,15,y2);
		move_sprite(2,15,y3);
		//paint p1
		move_sprite(3,153,y4);
		move_sprite(4,153,y5);
		move_sprite(5,153,y6);
		//paint ball
		move_sprite(6,ball_pos_x,ball_pos_y);
		//paint score
		move_sprite(7,15,140);
		move_sprite(8,153,140);
	}
}
 
